#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <pthread.h>

#define MAX_LEN 100

// Structure to hold parameters for the thread
typedef struct {
    int socket;
    struct sockaddr_in client;
    char host_name[MAX_LEN + 1];
} thread_data;

// Thread function to handle the DNS resolution
void* handle_request(void* arg) {
    thread_data* data = (thread_data*)arg;
    uint32_t ip_addr;
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    int status = getaddrinfo(data->host_name, NULL, &hints, &res);
    if (status == 0 && res != NULL) {
        struct sockaddr_in* ipv4 = (struct sockaddr_in*)res->ai_addr;
        ip_addr = ipv4->sin_addr.s_addr;
        sendto(data->socket, &ip_addr, sizeof(ip_addr), 0, (struct sockaddr*)&data->client, sizeof(data->client));
    } else {
        ip_addr = 0;
        sendto(data->socket, &ip_addr, sizeof(ip_addr), 0, (struct sockaddr*)&data->client, sizeof(data->client));
    }

    // Free allocated resources
    freeaddrinfo(res);
    free(data);
    return NULL;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: ./s [port_number]\n");
        return 1;
    }
    uint16_t port = atoi(argv[1]);

    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        printf("Server socket creation failed\n");
        return 1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(port);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Bind error\n");
        close(s);
        return 1;
    }

    while (1) {
        struct sockaddr_in client;
        int l_client = sizeof(client);
        char host_name[MAX_LEN + 1];

        int recv_len = recvfrom(s, host_name, MAX_LEN, MSG_WAITALL, (struct sockaddr*)&client, &l_client);
        if (recv_len < 0) {
            printf("Error receiving data\n");
            continue;
        }

        host_name[recv_len] = '\0';

        // Allocate memory for thread data and initialize it
        thread_data* data = malloc(sizeof(thread_data));
        if (data == NULL) {
            perror("Failed to allocate memory for thread data");
            continue;
        }
        
        data->socket = s;
        data->client = client;
        strncpy(data->host_name, host_name, MAX_LEN);

        // Create a thread to handle the request
        pthread_t tid;
        if (pthread_create(&tid, NULL, handle_request, data) != 0) {
            perror("Failed to create thread");
            free(data); // Clean up if thread creation fails
        }

        // Detach the thread to allow it to clean up after itself
        pthread_detach(tid);
    }

    close(s);
    return 0;
}
