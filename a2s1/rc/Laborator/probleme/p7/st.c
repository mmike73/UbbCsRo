#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

void *handle_client(void *arg) {
    int client_socket = *(int *)arg;
    free(arg);  // Free the dynamically allocated memory for client socket

    printf("S-a conectat un client!\n");	

    uint16_t len_sir;
    char *sir;

    // Receive the length of the string
    recv(client_socket, &len_sir, sizeof(len_sir), MSG_WAITALL);
    len_sir = ntohs(len_sir);

    // Allocate memory for the string and receive it
    sir = malloc((len_sir + 1) * sizeof(char));
    if (!sir) {
        perror("Memory allocation failed");
        close(client_socket);
        pthread_exit(NULL);
    }

    printf("Lungimea stringului: %d\n", len_sir);
    recv(client_socket, sir, len_sir * sizeof(char), MSG_WAITALL);
    sir[len_sir] = '\0';  // Null-terminate the string

    printf("Sirul: %s\n", sir);

    uint16_t start, noc;
    
    // Receive the start position and number of characters
    recv(client_socket, &start, sizeof(uint16_t), MSG_WAITALL);
    recv(client_socket, &noc, sizeof(uint16_t), MSG_WAITALL);

    start = ntohs(start);
    noc = ntohs(noc);

    printf("Start: %hu, Len: %hu\n", start, noc);

    // Send back the specified substring if within bounds
    if (start + noc <= len_sir) {
        send(client_socket, sir + start, noc * sizeof(char), 0);
    } else {
        printf("Requested substring out of bounds.\n");
    }

    // Cleanup
    free(sir);
    close(client_socket);
    pthread_exit(NULL);
}

int main(int argc, char** argv) {
    uint16_t port;

    // Argument parsing for port number
    if (argc > 1) {
        char* endptr;
        long port_long = strtol(argv[1], &endptr, 10);
        if (*endptr != '\0' || port_long <= 0 || port_long > 65535) {
            printf("Port invalid\n");
            return 1;
        } 
        port = (uint16_t)port_long;
    } else {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }

    // Create server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Nu s-a putut crea socketul server.\n");
        return 1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(port);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    // Bind server socket to address and port
    if (bind(server_socket, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("Eroare la bind");
        close(server_socket);
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        close(server_socket);
        return 1;
    }

    printf("Server is listening on port %d...\n", port);

    while (1) {
        struct sockaddr_in client;
        socklen_t client_len = sizeof(client);
        int *client_socket = malloc(sizeof(int));  // Allocate memory for client socket
        if (!client_socket) {
            perror("Memory allocation failed");
            continue;
        }

        // Accept a new client connection
        *client_socket = accept(server_socket, (struct sockaddr *)&client, &client_len);
        if (*client_socket < 0) {
            perror("Eroare la accept");
            free(client_socket);
            continue;
        }

        // Create a new thread to handle the client
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, client_socket) != 0) {
            perror("Failed to create thread");
            close(*client_socket);
            free(client_socket);
        }

        // Detach the thread so that resources are released when it's done
        pthread_detach(thread_id);
    }

    // Close server socket (unreachable in this example)
    close(server_socket);
    return 0;
}
