import struct

one_uint_struct_format = '!I'
one_uint_nb_bytes = struct.calcsize(one_uint_struct_format)
one_s_struct_format = '!s'
one_s_nb_bytes = struct.calcsize(one_s_struct_format)

whisperer_connection_port = 60000
vault_tcp_port = 60001