#!/usr/bin/env python3
import socket
import struct

from socket_conf import server_port, server_port_2, one_uint_struct_format, one_uint_nb_bytes

# socket creation
listening_socket = socket.socket()
listening_socket.bind(('localhost', server_port))
listening_socket.listen(1)

# accepting client
(connected_socket, client_address) = listening_socket.accept()

#receive random number
buf = connected_socket.recv(one_uint_nb_bytes)

(recv_data,) = struct.unpack(one_uint_struct_format, buf)

# picking a random number
send_data = 42

# send random number
connected_socket.sendall(struct.pack(one_uint_struct_format, send_data))

# close connection
connected_socket.shutdown(socket.SHUT_RDWR)
connected_socket.close()
listening_socket.close()

# print result
print(f'Sended data: {send_data}')
print(f'recv data: {recv_data}')

