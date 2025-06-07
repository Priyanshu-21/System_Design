#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main (void) {
    int socket_desc;
    struct sockaddr_in server_add, client_add; // Describing internet socket addresses 
    char server_message[200], client_message[200];  // Contains server & client message 
    int client_add_length = sizeof(client_add);

    // Creating a UDP Socket 
    socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socket_desc < 0) {
        printf("Cannot create the socket: %d\n", socket_desc);
        return -1;
    }
    // Set the protocol, server port, server IP address 
    server_add.sin_family = AF_INET;
    server_add.sin_port = htons(8080);
    server_add.sin_addr.s_addr = inet_addr("127.0.0.1");

    // binding socket desc with server's details 
    if (bind(socket_desc, (struct sockaddr*)&server_add, sizeof(server_add)) < 0) {
        printf("Cannot Bind the file descriptor.\n");
        return -1;
    }

    // Recieve the Client datagram, message form: Binary
    if (recvfrom(socket_desc, client_message, sizeof(client_message), 0, (struct sockaddr*)&client_add, &client_add_length) < 0) {
        printf("Unable to Receive datagram from client.\n");
        return -1;
    }
    
    // Recived the datagram from the client
    printf("Received the message from Client: %s and listening on port %d", inet_ntoa(client_add.sin_addr), htons(client_add.sin_port));

    // Message from the client 
    printf("\nReceived the message: %s\n", client_message);

    //Sent the datagram to client 
    strcpy(server_message, client_message);
    if (sendto(socket_desc, server_message, strlen(server_message), 0, (struct sockaddr*)&client_add, client_add_length) < 0) {
        printf("Cannot Send datagram to client.\n");
        return -1;
    }

    // Close the Socket 
    close(socket_desc);
    return 0;
}