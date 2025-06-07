#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char** argv) {
	uint16_t port;

	if (argc > 1) {
		char* endptr;
		long port_long = strtol(argv[1], &endptr, 10);

		if (*endptr != '\0' || port_long <= 0 || port_long > 65535) {
			printf("Port invalid!\n");
			return 1;
		}
		port = (uint16_t)port_long;
	} else {
		printf("Usage: ./c port_number\n");
		return 1;
	}

	int c = socket(AF_INET, SOCK_DGRAM, 0);
	if (c < 0) {
		printf("Eroare la crearea socketului client\n");
		return 1;
	}

	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(port);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("192.168.64.24");

	int l = sizeof(server);
	
	uint16_t a, b;

	printf("Introdu 2 numere: ");
	scanf("%hu %hu", &a, &b);
	
	a = htons(a);
	b = htons(b);

	sendto(c, &a, sizeof(a), 0, (struct sockaddr *) &server, l);
	sendto(c, &b, sizeof(b), 0, (struct sockaddr *) &server, l);

	uint16_t  cmmdc, cmmmc;

	recvfrom(c, &cmmdc, sizeof(cmmdc), MSG_WAITALL, (struct sockaddr *) &server, &l);
	recvfrom(c, &cmmmc, sizeof(cmmmc), MSG_WAITALL, (struct sockaddr *) &server, &l);
	
	cmmdc = ntohs(cmmdc);
	cmmmc = ntohs(cmmmc);

	a = ntohs(a);
	b = ntohs(b);	

	printf("Cmmdc(%hu, %hu) = %hu\n", a, b, cmmdc);
	printf("Cmmmc(%hu, %hu) = %hu\n", a, b, cmmmc);

	close(c);
}
