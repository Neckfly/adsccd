#!/usr/bin/env python3
import socket
import struct

from socket_conf import one_uint_struct_format, one_uint_nb_bytes, whisperer_connection_port, vault_tcp_port, one_s_struct_format, one_s_nb_bytes

# socket creation
# python 3.8 : listening_socket = socket.create_server(('localhost', 60000))
listening_socket = socket.socket()
listening_socket.bind(('localhost', whisperer_connection_port))
listening_socket.listen(1)

# accepting client
(connected_socket, client_address) = listening_socket.accept()

#receive 1
buf = connected_socket.recv(one_uint_nb_bytes)

(size,) = struct.unpack(one_uint_struct_format, buf)
print('nbOctet' + str(size))

buf = connected_socket.recv(size)
print("buffer " + str(buf))

# close connection
connected_socket.shutdown(socket.SHUT_RDWR)
connected_socket.close()
listening_socket.close()

connected_socket = socket.create_connection(('localhost', vault_tcp_port))

connected_socket.sendall(struct.pack(one_uint_struct_format, size))

connected_socket.sendall(buf)

#receive price
buf = connected_socket.recv(one_uint_nb_bytes)

(price,) = struct.unpack(one_uint_struct_format, buf)
print('treasure :' + str(price))