#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

uint8_t divisor_helper(uint8_t** divizori, uint8_t num) {
    uint8_t div[100] = {0};
    uint8_t cnt = 0;
    uint8_t d;

    for (d = 1; d * d < num; ++d) {
        if (num % d == 0) {
            div[cnt++] = d;
            div[cnt++] = num / d;
        }
    }

    if (d * d == num)
        div[cnt++] = d;

    // Allocate memory for divizori and copy values
    *divizori = malloc(cnt * sizeof(uint8_t));
    if (*divizori == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < cnt; ++i)
        (*divizori)[i] = div[i];

    return cnt;
}

int main(int argc, char **argv) {

    uint16_t port;
    if (argc > 1) {
        char *endptr;
        long port_long = strtol(argv[1], &endptr, 10);
        if (*endptr != '\0' || port_long <= 0 || port_long > 65535) {
            printf("Port invalid\n");
            return 1;
        }
        port = (uint16_t)port_long;
    } else {
        printf("Introdu ca argument portul la care sa asculte serverul!\n");
        return 1;
    }

    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        printf("Eroare la crearea socketului server!\n");
        return 1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(port);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("Eroare la bind\n");
        return 1;
    }

    struct sockaddr_in client;
    int l = sizeof(client);
    
    uint8_t num;

    while (1) {
        memset(&client, 0, l);
        recvfrom(s, &num, sizeof(num), MSG_WAITALL, (struct sockaddr *) &client, &l);

        printf("Recvd %hhu\n", num);

        uint8_t* divizori = NULL;
        uint8_t nrdiv = divisor_helper(&divizori, num);

        sendto(s, &nrdiv, sizeof(nrdiv), 0, (struct sockaddr *) &client, l);

        printf("Number of divisors: %hhu\n", nrdiv);

        sendto(s, divizori, nrdiv * sizeof(uint8_t), 0, (struct sockaddr *) &client, l);

        printf("Divisors: ");
        for (int i = 0; i < nrdiv; ++i) {
            printf("%hhu ", divizori[i]);
        }
        printf("\n");

        free(divizori);
    }

    close(s);
    return 0;
}
