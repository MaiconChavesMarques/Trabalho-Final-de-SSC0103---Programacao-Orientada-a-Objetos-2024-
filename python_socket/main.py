import subprocess
import socket

def handle_client_connection(client_socket, nomePrograma: str) -> None:
    """Funcao que lida com a conexao do cliente
    
    Args:
        client_socket (socket): socket do cliente
        nomePrograma (str): nome do programa em C
    """
    # Start the C program using subprocess
    process = subprocess.Popen([nomePrograma], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    try:
        while True:
            # Receive data from the socket
            data = client_socket.recv(1024)
            if not data:
                break

            # Send the data to the C program
            process.stdin.write(data)
            process.stdin.flush()

            # Read the response from the C program
            response = process.stdout.readline()

            # Send the response back to the client
            client_socket.sendall(response)
    finally:
        # Clean up the connection and the process
        client_socket.close()
        process.terminate()


def start_server(nomePrograma, port = 8888, ip = "0.0.0.0"):
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((ip, port))
    server_socket.listen(5)
    print('Server listening on port 8888')

    while True:
        client_socket, addr = server_socket.accept()
        print(f'Accepted connection from {addr}')
        handle_client_connection(client_socket, nomePrograma)


if __name__ == '__main__':
    start_server("./main")