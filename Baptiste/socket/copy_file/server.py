#!/usr/bin/env python3
import socket

from socket_conf import server_port, server_port_2

# create the server socket
listening_socket = socket.socket()
listening_socket.bind(('localhost', server_port))
listening_socket.listen(1)

# accept the client socket
(connected_socket, client_address) = listening_socket.accept()

# open file
f = open('output_file', 'wb')

# receive data
buf = connected_socket.recv(1024)
while buf:
    buf = connected_socket.recv(1024)

# close connection
connected_socket.shutdown(socket.SHUT_RDWR)
connected_socket.close()
listening_socket.close()

# end
print('Server finished to copy.')
