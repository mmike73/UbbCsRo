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
	
	

	int s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		printf("Nu s-a putut crea socketul server.\n");
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

	listen(s, 5);

	struct sockaddr_in client;
	memset(&client, 0, sizeof(client));
	int l = sizeof(client), c;

	while (1) {

		c = accept(s, (struct sockaddr *) &client, &l);
		printf("S-a conectat un client!\n");	

		uint16_t len_sir;
		char* sir;

		recv(c, &len_sir, sizeof(len_sir), MSG_WAITALL);

		len_sir = ntohs(len_sir);
		sir = malloc((len_sir + 1) * sizeof(char));
	
		printf("Lungimea stringului: %d\n", len_sir);

		recv(c, sir, len_sir * sizeof(char), MSG_WAITALL);

		printf("Sirul: %s\n", sir);
		
		uint16_t start, noc;

		recv(c, &start, sizeof(uint16_t), MSG_WAITALL);

		recv(c, &noc, sizeof(uint16_t), MSG_WAITALL);

		start = ntohs(start);

		noc = ntohs(noc);

		printf("Start: %hu, Len: %hu\n", start, noc);

		if (start + noc < len_sir) {
			
			send(c, sir + start, noc * sizeof(char), 0);
		}

		free(sir);
		close(c);
		
	}
	close(s);
}	
