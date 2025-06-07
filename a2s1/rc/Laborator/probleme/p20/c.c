#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#define MAX_LEN 100


int main(int argc, char** argv) {

    if (argc < 2) {
        printf("Usage: ./c [port_number]\n");
        return 1;
    }

    uint16_t port = atoi(argv[1]);

    int c = socket(AF_INET, SOCK_DGRAM, 0);
    if (c < 0) {
        printf("Client socket creation failed");
        return 1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(port);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("192.168.64.24");

    char hostname[MAX_LEN + 1];
    printf("Enter hostname: ");
    scanf("%s", hostname);

    // fgets(hostname, MAX_LEN, stdin);
    // hostname[strcspn(hostname, '\n')] = '\0';

    uint16_t l = sizeof(server);

    if (sendto(c, hostname, strlen(hostname), 0, (struct sockaddr *) &server, l) < 0) {
        printf("Error sending message\n");
        close(c);
        exit(1);
    }

    uint32_t ip_addr;
    int l_s = sizeof(struct sockaddr_in);
    
    if (recvfrom(c, &ip_addr, sizeof(ip_addr), 0, (struct sockaddr *) &server, &l_s) < 0) {
        printf("Error receiving message\n");
        close(c);
        exit(1);
    }

    if (ip_addr == 0) {
        printf("Hostname not found\n");
    } else {
        struct in_addr addr;
        addr.s_addr = ip_addr;
        printf("IP of hosname: %s\n", inet_ntoa(addr));
    }
    close(c);
}