//3571
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char** argv) {

	int c = socket(AF_INET, SOCK_STREAM, 0);
	if (c < 0) {
		printf("Nu s-a putut crea socketul client\n");
		return 1;
	}

	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(8889);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("172.30.240.4");
	
	if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0){
		printf("Eroare de conectare la server");
		return 1;
	}

	uint16_t num = 3571;
    uint16_t l = 0;
	
    num = htons(num);
	send(c, &num, sizeof(num), 0);
    num = ntohs(num);
	
    recv(c, &l, sizeof(l), MSG_WAITALL);    

    printf("Got the length %hhu\n", l);

    char rez[10001];
	recv(c, rez, l * sizeof(char), MSG_WAITALL);

    printf("%s\n", rez);

    uint16_t l1 = strlen(rez);

    l1 = htons(l1);

    send(c, &l1, sizeof(l1), 0);
	
    uint8_t size;
    char buff[10001]; 
    uint16_t index = 0;
    while (1) {
        recv(c, &size, sizeof(size), MSG_WAITALL);

        if (size == 0) break;

        printf("Got the length %hhu\n", size);

        recv(c, buff + index, size * sizeof(char), MSG_WAITALL);

        index += size;

    }

    index = htons(index);

	send(c, &index, sizeof(index), 0);
        

    printf("%s\n", buff);

	close(c);
}

