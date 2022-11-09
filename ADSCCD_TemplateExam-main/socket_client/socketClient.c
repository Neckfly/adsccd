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
int connected_socket;

/* creating a tcp-IPv4 socket*/
connected_socket = socket(AF_INET, SOCK_STREAM, 0);
if (connected_socket == -1) {
    fprintf(stderr, "Client error on creating the socket : %d, %s.\n",
                    errno, strerror(errno));
    exit(EXIT_FAILURE);
}

/* connect socket */
server_address.sin_family = AF_INET;
server_address.sin_port = htons(TCP_PORT);
if (!inet_aton(SERVER_IPV4_ADDR, &server_address.sin_addr)) {
    fprintf(stderr, "Client socket adress is not valid : %s \n",
                    SERVER_IPV4_ADDR);
}

if (connect(connected_socket, (struct sockaddr *)&server_address,
            sizeof(server_address))) {
    fprintf(stderr, "Client error on connecting socket : %d , %s .\n",
                    errno, strerror(errno));
}
