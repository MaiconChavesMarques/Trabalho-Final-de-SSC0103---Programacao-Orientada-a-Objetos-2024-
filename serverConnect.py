import socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('127.0.0.1', 8888))
try:
    while True:
        message = input("Enter message: ")
        if not message:
            break
        message += "\0"
        client_socket.sendall(message.encode())
        response = client_socket.recv(1024)
        print("Received:", response.decode())
        response = None
finally:
    client_socket.close()
