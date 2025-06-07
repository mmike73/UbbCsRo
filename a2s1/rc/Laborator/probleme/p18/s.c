#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

uint16_t computeCmmdc(uint16_t a, uint16_t b) {
	if (b == 0) return a;
	if (b > a) return computeCmmdc(a, b % a);
	return computeCmmdc(b, a % b);
}

uint16_t computeCmmmc(uint16_t a, uint16_t b) {
	return a / computeCmmdc(a, b) * b;
}

int main(int argc, char** argv) {
	
	uint16_t port;

	if (argc > 1) {
		char* endptr;
		long port_long = strtol(argv[1], &endptr, 10);

		if (*endptr != '\0' || port_long <= 0 || port_long > 65535) {
			printf("Port invalid\n");
			return 1;
		}
		port = (uint16_t) port_long;
	} else {
		printf("Usage: ./%s port\n", argv[0]);
		return 1;
	}

	int s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0) {
	      	printf("Eroare la crearea socketului server\n");
       		return 1;
	}

	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(port);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	printf("Started in port %hu\n", port);

	if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la bind\n");
		return 1;
	}

	struct sockaddr_in client;
	int l = sizeof(client);

	while (1) {			
		memset(&client, 0, sizeof(client));
		
		uint16_t a, b;

		recvfrom(s, &a, sizeof(a), MSG_WAITALL, (struct sockaddr *) &client, &l);

		recvfrom(s, &b, sizeof(b), MSG_WAITALL, (struct sockaddr *) &client, &l);

		a = ntohs(a);
		b = ntohs(b);

		printf("Recv %hu, %hu\n", a, b);

		uint16_t cmmdc = computeCmmdc(a, b);
		uint16_t cmmmc = computeCmmmc(a, b);
		
		printf("Cmmdc: %hu\n", cmmdc);
		printf("Cmmmc: %hu\n", cmmmc);

		cmmdc = htons(cmmdc);
		cmmmc = htons(cmmmc);

		sendto(s, &cmmdc, sizeof(cmmdc), 0, (struct sockaddr *) &client, l);
		sendto(s, &cmmmc, sizeof(cmmmc), 0, (struct sockaddr *) &client, l);
	}
	close(s);
}
