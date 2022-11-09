/* Envoi de messages */
client_id = htonl(client_id);
msg_size = send(giver_socket, &client_id, sizeof(client_id), 0);
if (msg_size == -1) {
    fprintf(stderr, "Client error when sending client id: %d , %s .\n",
                    errno, strerror(errno));
}

if (msg_size < sizeof(client_id)) {
    fprintf(stderr, "Client only sends %ld bytes instead of %ld .\n",
                    msg_size, sizeof(client_id));
}

client_id = ntohl(client_id);
printf("Client sent its id %u to the giver server.\n", client_id);



/* Reception de messages */
msg_size = recv(giver_socket, &client_key, sizeof(client_key), 0);
if (msg_size == -1) {
    fprintf(stderr, "Client error when receiving mystery key: %d , %s .\n",
                    errno, strerror(errno));
}

if (msg_size < sizeof(client_key)) {
    fprintf(stderr, "Client only receives %ld bytes instead of %ld .\n",
                    msg_size, sizeof(client_key));
}

client_key = ntohl(client_key);
printf("Client received the mystery key %u .\n", client_key);