#!/usr/bin/env python3
import socket

from socket_conf import server_port, server_port_2

# create and connect the socket
connected_socket = socket.create_connection(('localhost', server_port))

# open file
f = open('input_file.txt', 'rb')

buf = f.read(1024)
while len(buf):
    connected_socket.sendall(buf)
    buf = f.read(1024)

# close socket
connected_socket.shutdown(socket.SHUT_RDWR)
connected_socket.close()

# end
print('Client finished to read and to send.')
