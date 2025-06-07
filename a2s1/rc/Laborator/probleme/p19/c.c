#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#include <time.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: ./c [port_number]\n");
        return 1;
    }

    uint16_t port = atoi(argv[1]);

    int c = socket(AF_INET, SOCK_DGRAM, 0);
    if (c < 0) {
        printf("Failed to create client socket\n");
        return 1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(port);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("192.168.64.24");

    int l = sizeof(server);


    uint64_t nrsec;

    char req = 'r';
    if (sendto(c, &req, 1, 0, (struct sockaddr *) &server, l) < 0) {
        printf("Packet transfer error\n");
        close(c);
        return 1;
    }

    if (recvfrom(c, &nrsec, sizeof(nrsec), MSG_WAITALL, (struct sockaddr *) &server, &l) < 0) {
        printf("Packet transfer error\n");
        close(c);
        return 1;
    }

    printf("%u\n", nrsec);
    time_t server_time = (time_t)nrsec;
    struct tm *local_time = localtime(&nrsec);

    printf("Current time and date is: %s\n", asctime(local_time));

    return 0;

}

/*
int year = datetime_int / 100000000;          // 2021
    int month = (datetime_int / 1000000) % 100;  // 12
    int day = (datetime_int / 10000) % 100;      // 01
    int hour = (datetime_int / 100) % 100;        // 12
    int minute = datetime_int % 100;              // 30
    int second = 0;    
    
    struct tm date = {0};
    date.tm_year = year - 1900; // tm_year is year since 1900
    date.tm_mon = month - 1;     // tm_mon is 0-11
    date.tm_mday = day;          // Day of the month
    date.tm_hour = hour;         // Hour (0-23)
    date.tm_min = minute;        // Minutes (0-59)
    date.tm_sec = second;   */