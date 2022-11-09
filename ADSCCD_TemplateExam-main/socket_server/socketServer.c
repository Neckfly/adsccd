#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#include "socket_tcp_conf.h"

/* socket variables */
struct sockaddr_in server_address;
struct sockaddr_in client_address;
socklen_t client_address_len = sizeof(client_address);
int listening_socket;
int connected_socket;

/* creating a tcp-IPv4 socket*/
listening_socket = socket(AF_INET, SOCK_STREAM, 0);
if (listening_socket == -1) {
    fprintf(stderr, "Server error on creating the socket : %d, %s.\n",
                    errno, strerror(errno));
    exit(EXIT_FAILURE);
}

/* bind socket */
server_address.sin_family = AF_INET;
server_address.sin_port = htons(TCP_PORT);
if (!inet_aton(SERVER_IPV4_ADDR, &server_address.sin_addr)) {
    fprintf(stderr, "Server socket adress is not valid : %s \n",
                    SERVER_IPV4_ADDR);
}
if (bind(listening_socket, (struct sockaddr *)&server_address,
         sizeof(server_address))) {
    fprintf(stderr, "Server error on binding : %d , %s .\n",
                    errno, strerror(errno));
}

/* listen */
if (listen(listening_socket, MAX_CLIENT)) {
    fprintf(stderr, "Server unable to listen %d max client : %d , %s .\n",
                    MAX_CLIENT, errno, strerror(errno));
    goto clean_listening;
}

/* accept one connection */
connected_socket = accept(listening_socket,
                          (struct sockaddr *)&client_address,
                          &client_address_len);
if (connected_socket == -1) {
    fprintf(stderr, "Server error on accepting socket : %d , %s .\n",
                    errno, strerror(errno));
}

if (client_address_len > sizeof(client_address)) {
    fprintf(stderr, "Server error on accepting a client address size too "
                    "large : %d accepted, instead of %ld .\n",
                    client_address_len, sizeof(client_address));
}


