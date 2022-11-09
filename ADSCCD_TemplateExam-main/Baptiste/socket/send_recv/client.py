#!/usr/bin/env python3
import socket
import struct

from socket_conf import server_port, server_port_2, one_uint_struct_format, one_uint_nb_bytes

# connection to the server
connected_socket = socket.create_connection(('localhost', server_port))

# picking a random number
send_data = 42

# send
connected_socket.sendall(struct.pack(one_uint_struct_format, send_data))

#receive
buf = connected_socket.recv(one_uint_nb_bytes)

(recv_draw,) = struct.unpack(one_uint_struct_format, buf)

# close connection
connected_socket.shutdown(socket.SHUT_RDWR)
connected_socket.close()

# print result
print(f'sended data: {send_data}')
print(f'recv data: {recv_draw}')

