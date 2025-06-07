#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#include <pthread.h>
#include <time.h>

typedef struct {
    int socket;
    struct sockaddr_in client;
} thread_data;

void* handle_request(void* arg) {
    thread_data* data = (thread_data *) arg;

    uint32_t seconds = time(NULL);
    int size_cl = sizeof(data->client);

    sendto(data->socket, &seconds, sizeof(seconds), 0, (struct sockaddr*) &data->client, size_cl);

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
        printf("Client socket could not be created\n");
        return 1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(port);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    int l = sizeof(server);

    //BIND
    if (bind(s, (struct sockaddr*) &server, sizeof(server)) < 0) {
        printf("Bind error");
        close(s);
        return 1;
    }

    while (1) {
        struct sockaddr_in client;
        int l_c = sizeof(client);

        char req = '\0';
        int req_len =  recvfrom(s, &req, 1, MSG_WAITALL, (struct sockaddr *) &client, &l_c);
        if (req_len != 1) {
            printf("Bad req\n");
            continue;
        }

        printf("Client request intercepted\n");

        thread_data* data = malloc(sizeof(thread_data));

        data->socket = s;
        data->client = client;

        pthread_t tid;
        
        pthread_create(&tid, NULL, handle_request, data);

        pthread_detach(tid);
    }

    close(s);
}