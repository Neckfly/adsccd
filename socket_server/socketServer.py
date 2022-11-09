import socket

from socket_tcp_settings import server_address,server_port

#Creation et paramètrage de la socket
listening_socket = socket.socket()
listening_socket.bind((server_address, server_port))

# Attente et acceptation client
print(f"Checker is waiting for connection")
listening_socket.listen(1)
(connected_socket, client_address) = listening_socket.accept()
print(f"Checker paired succesfully")