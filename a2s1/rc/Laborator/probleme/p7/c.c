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
	uint16_t port;

	if (argc > 1) {
		char* endptr;
		long port_long = strtol(argv[1], &endptr, 10);
		if (*endptr != '\0' || port_long <= 0 || port_long > 65535) {
			printf("Port invalid\n");
			return 1;
		}
		port = (uint16_t)port_long;
	} else {
		printf("Usage: %s <port>\n", argv[0]);
        return 1;
	}

	int c = socket(AF_INET, SOCK_STREAM, 0);
	if (c < 0) {
		printf("Nu s-a putut crea socketul client\n");
		return 1;
	}

	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(port);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("192.168.64.24");
	
	if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0){
		printf("Eroare de conectare la server");
		return 1;
	}

	uint16_t i, l, len_sir;
	char* sir = malloc(101);
	
	printf("Introdu un sr de caractere: ");
	fgets(sir, 100, stdin);

	sir[strlen(sir)] = '\0';

	printf("Sirul: %s\n", sir);


	len_sir = strlen(sir);

	len_sir = htons(len_sir);
	send(c, &len_sir, sizeof(len_sir), 0);
	len_sir = ntohs(len_sir);

	printf("Lungimea stringului: %d\n", len_sir);


	send(c, sir, len_sir * sizeof(char), 0);

	printf("Introdu positie se unde sa inceapa subsirul: ");
	scanf("%hu", &i);

	printf("Introdu lungimea subssirului dorit: ");
	scanf("%hu", &l);

	i = htons(i);
	send(c, &i, sizeof(i), 0);
	i = ntohs(i);

	l = htons(l);
	send(c, &l, sizeof(l), 0);
	l = ntohs(l);

			
	printf("Start: %hu, Len: %hu\n", i, l);


	char* rez = malloc((l + 1)* sizeof(char));
	recv(c, rez, l * sizeof(char), MSG_WAITALL);
	
	printf("Subsirul: %s\n", rez);

	free(rez);
	free(sir);
	close(c);
}
