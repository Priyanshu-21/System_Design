#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(void) {
    // Description of the client and server address 
    int socket_desc;
    struct sockaddr_in server_add;
    char server_message[200], client_message[200];
    int server_add_length = sizeof(server_add);

    // Define the Socket 
    socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socket_desc < 0) {
        printf("Cannot create the socket.\n");
        return -1;
    }
    // Description of client Address, port and Protocol used 
    server_add.sin_family = AF_INET;
    server_add.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_add.sin_port = htons(8080);

    // Send Message to server 
    printf("Enter the message to send to server: \n");
    gets(client_message);

    if (sendto(socket_desc, client_message, strlen(client_message), 0, (struct sockaddr*)&server_add, server_add_length) < 0) {
        printf("Cannot Send the message to Server.\n");
        return -1;
    }

    // Recieve the message from server 
    if (recvfrom(socket_desc, server_message, sizeof(server_message), 0, (struct sockaddr *)&server_add, &server_add_length) < 0) {
        printf("Cannot receive message from server.\n");
        return -1;
    }

    // Print the message received from the server 
    printf("Message from the server: %s\n", server_message);

    // Close the file Descriptor 
    close(socket_desc);
    return 0;
}