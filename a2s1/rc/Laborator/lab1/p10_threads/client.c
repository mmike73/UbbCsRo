#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include <sys/types.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	int c;
	c = socket(AF_INET, SOCK_STREAM, 0);
	if (c < 0) {
		printf("Eroare la crearea socketului client\n");
		return 1;
	}

	struct sockaddr_in server;

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(57576);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("192.168.64.25");

	if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la conectarea la server\n");
		return 1;
	}
	
	char *s1, *s2;
	uint16_t res_cnt;
	char res;

	s1 = malloc(101);
	s2 = malloc(101);

	printf("Introdu primul string: ");
	
	fgets(s1, 101, stdin);
	s1[strcspn(s1, "\n")] = '\0';

	printf("Introdu al doilea string: ");

	fgets(s2, 101, stdin);
	s2[strcspn(s2, "\n")] = '\0';

	uint16_t l1, l2;

	l1 = strlen(s1);
	l2 = strlen(s2);

	l1 = htons(l1);
	l2 = htons(l2);

	send(c, &l1, sizeof(l1), 0);
	l1 = ntohs(l1);

	send(c, s1, l1, 0);
	
	send(c, &l2, sizeof(l2), 0);
	l2 = ntohs(l2);

	send(c, s2, l2, 0);

	recv(c, &res, 1, 0);

	recv(c, &res_cnt, sizeof(res_cnt), 0);

	res_cnt = ntohs(res_cnt);
	
	printf("%c de %hd ori\n", res, res_cnt);

	free(s1);
	free(s2);

	close(c);
}
