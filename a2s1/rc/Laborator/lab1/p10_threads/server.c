#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <pthread.h>

int main() {

	int s; // descriptorul serverului
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		printf("Eroare la crearea socketului server\n");
		return 1;
	}
	
	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));

	server.sin_port = htons(57576);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la bind\n");
		return 1;
	}

	listen(s,5);


	struct sockaddr_in client;
	int l;
	l = sizeof(client);

	memset(&client, 0, sizeof(client));

	int c; // descriptorul clientului
	while (1) {
		c = accept(s, (struct sockaddr *) &client, &l);
		printf("S-a conectat clientul\n");
		
		/// desfasurarea actiunii

		uint16_t l1, l2;
		char *s1, *s2;

		recv(c, &l1, sizeof(l1), MSG_WAITALL);

		l1 = ntohs(l1);

		if (l1 > 101) {
			printf("Input prea mare, maxim 100 de caractere!!!");
			continue;			
		}
		
		s1 = malloc(101 * sizeof(char));

		recv(c, s1, l1 * sizeof(char), MSG_WAITALL);

		recv(c, &l2, sizeof(l2), MSG_WAITALL);
		
		l2 = ntohs(l2);

		if (l2 > 101) {
			printf("Input prea mare, maxim 100 de caractere!!!");
			free(s1);
			continue;	
		}

		s2 = malloc(101 * sizeof(char));

		recv(c, s2, l2 * sizeof(char), MSG_WAITALL); 
		
		printf("S2: %s, length: %hd", s2, l2);

		uint16_t n;
		if (l1 > l2) n = l2;
		else n = l1;

		int* occ = malloc(26 * sizeof(int));
		memset(occ, 0, 26 * sizeof(int));

		for (int i = 0; i < n; ++i)
			if (s1[i] >= 'a' && s1[i] <= 'z')
				if (s1[i] == s2[i]) {
					occ[s1[i] - 'a'] += 2;
				}
		
		char rez = '\0';
	      	uint16_t cnt_rez = 0;
		for (int i = 0; i < 26; ++i)
				if (occ[i] > cnt_rez) {
					cnt_rez = occ[i];
					rez = 'a' + i;
				}
		
		printf("In\n %s  %s \n apare %c de %hd ori\n", s1, s2, rez, cnt_rez);

		cnt_rez = htons(cnt_rez);
		
		send(c, &rez, sizeof(char), 0);
		send(c, &cnt_rez, sizeof(cnt_rez), 0);	

		free(s1);
		free(s2);
		free(occ);
		close(c);
	}
}
