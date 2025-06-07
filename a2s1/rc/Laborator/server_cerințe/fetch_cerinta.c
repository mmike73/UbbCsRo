#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <netinet/in.h>
#include <netinet/ip.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
	
	int c;
	c = socket(AF_INET, SOCK_STREAM, 0);
	if (c < 0) {
		printf("Eroare la crearea socketului client.\n");
		return 1;
	}

	struct sockaddr_in client;
	memset(&client, 0, sizeof(client));
	client.sin_port = htons(54321);
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = inet_addr("192.168.64.24");

	if (connect(c, (struct sockaddr *) &client, sizeof(client)) < 0) {
		printf("Eroare la conectarea cu serverul!\n");
		return 1;
	}

	uint16_t l;
	recv(c, &l, 2, MSG_WAITALL);
	l = ntohs(l);

	char* message = malloc(l + 1);
	recv(c, message, l, MSG_WAITALL);

	printf("Problema de rezolvat: %s\n");

	free(message);
	
	close(c);
	return 0;
}
