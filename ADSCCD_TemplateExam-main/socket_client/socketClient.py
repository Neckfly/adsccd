import socket

from socket_tcp_settings import server_address, server_port, struc_nb_bytes

#Creation de la socket client
connected_socket = socket.create_connection((server_address, server_port))
print(f"Client paired succesfully")