import socket
import ctypes
import os
import threading

libc = ctypes.CDLL('/home/rodrigo/Documents/GitHub/Trabalho-Final-de-SSC0103---Programacao-Orientada-a-Objetos-2024-/arquivos/libbiblioteca.so')

main = libc.main
main.restype = ctypes.c_int
main.argtypes = []

# Create a lock
command_lock = threading.Lock()

def handle_client(client_socket):
    try:
        buffer = ""
        while True:
            # Receive data from the client
            data = client_socket.recv(1024).decode()
            if not data:
                break
            
            buffer += data
            if '\0' in buffer:
                lines = buffer.split('\0')
                for line in lines:
                    if not line.strip():
                        continue

                    with command_lock:  # Acquire the lock before processing
                        print("Received:", repr(line.strip()))  # Use repr to show special characters
                        print("First character:", repr(line.strip()[0]))

                        # Redirect stdin to simulate user input for the C function
                        read_fd, write_fd = os.pipe()
                        input_data = line.strip() + "\n"
                        os.write(write_fd, input_data.encode())
                        os.close(write_fd)

                        # Save the original stdin file descriptor
                        original_stdin = os.dup(0)
                        os.dup2(read_fd, 0)
                        os.close(read_fd)

                        # Redirect stdout to capture the output
                        stdout_read_fd, stdout_write_fd = os.pipe()
                        original_stdout = os.dup(1)
                        os.dup2(stdout_write_fd, 1)
                        os.close(stdout_write_fd)

                        try:
                            # Process data using the C function
                            print("Calling main()")
                            main()
                        finally:
                            # Restore the original stdin
                            os.dup2(original_stdin, 0)
                            os.close(original_stdin)

                            # Restore the original stdout
                            os.dup2(original_stdout, 1)
                            os.close(original_stdout)

                        # Read the output from the stdout pipe
                        captured_output = os.read(stdout_read_fd, 64000).decode()
                        os.close(stdout_read_fd)

                        captured_output += "\0"

                        print("Sending:", repr(captured_output))  # Use repr to show special characters

                        # Send the captured output back to the client
                        client_socket.sendall(captured_output.encode())
                
                # Reset the buffer with any remaining data
                buffer = lines[-1]

    finally:
        client_socket.close()


def main_server():
    # Create a socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('127.0.0.1', 8888))
    server_socket.listen(5)

    print("Server listening on port 8888...")

    try:
        while True:
            # Accept a client connection
            client_socket, client_address = server_socket.accept()
            print(f"Connection from {client_address}")

            # Create a new thread to handle the client
            client_thread = threading.Thread(target=handle_client, args=(client_socket,))
            client_thread.daemon = True  # Ensure thread exits when the main thread does
            client_thread.start()

    finally:
        server_socket.close()

if __name__ == "__main__":
    main_server()
