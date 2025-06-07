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

#define MAX_LEN 100

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

    if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("Bind error\n");
        close(s);
        return 1;
    }

    struct sockaddr_in client;
    int l_client = sizeof(client);

    while (1) {
        memset(&client, 0, sizeof(client));

        char host_name[MAX_LEN + 1];

        int recv_len = recvfrom(s, host_name, MAX_LEN, MSG_WAITALL, (struct sockaddr *) &client, &l_client);

        if (recv_len < 0) {
            printf("Error receiving data");
            continue;
        }

        host_name[recv_len] = '\0';

        struct addrinfo hints, *res;

        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_DGRAM;

        int status = getaddrinfo(host_name, NULL, &hints, &res);
        uint32_t ip_addr;

        if (status == 0 && res != NULL) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *) res->ai_addr;
            ip_addr = ipv4->sin_addr.s_addr;

            sendto(s, &ip_addr, sizeof(ip_addr), 0, (struct sockaddr *) &client, l_client);
        } else {
            ip_addr = 0;
            sendto(s, &ip_addr, sizeof(ip_addr), 0, (struct sockaddr *) &client, l_client);
        }
    }
    close(s);
}
