#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv) {
	uint16_t port;

	if (argc > 1) {
		char *endptr;
		long port_long = strtol(argv[1], &endptr, 10); // Use argv[1] directly
		if (*endptr != '\0' || port_long <= 0 || port_long > 65535) {
			printf("Port invalid\n");
			return 1;
		}
		port = (uint16_t)port_long;
	} else {
		printf("Introdu ca parametru portul serverului");
		return 1;
	}

	int c = socket(AF_INET, SOCK_DGRAM, 0);
	if (c < 0) {
		printf("Eroare la crearea socketului client\n");
		return 1;
	}

	printf("Client sends to 192.168.64.24, port %hu\n", port);
	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(port);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("192.168.64.24");

	printf("Started server on port %d\n",port);

	uint8_t k;
	printf("Introdu un numar (< 255): ");
	scanf("%hhu", &k);


	int l = sizeof(server);
	sendto(c, &k, 1, 0, (struct sockaddr *) &server, l);
	
	uint8_t nrdiv;
	recvfrom(c, &nrdiv, 1, MSG_WAITALL, (struct sockaddr*) &server, &l);

	printf("%hhu\n", nrdiv);

	uint8_t* divizori = malloc(nrdiv);
	recvfrom(c, divizori, nrdiv, MSG_WAITALL, (struct sockaddr*) &server, &l);

	for (int i = 0; i < nrdiv; ++i) {
		printf("%hhu ", divizori[i]);
	}

	printf("\n");


	close(c);
}
