#Envoi de messages.
connected_socket.sendall(struct.pack(one_int_struct_format, var))

#reception de messages
buf = connected_socket.recv(one_int_nb_bytes)
if len(buf) != one_int_nb_bytes:
    raise IOError(f'Client partial read: {len(buf)} instead of {one_int_nb_bytes}')

(client_key,) = struct.unpack(one_int_struct_format, buf)
