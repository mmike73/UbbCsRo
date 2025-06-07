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

	printf("Creare socket\n");


	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(8889);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("172.30.240.4");

	printf("Sockaddr_in\n");

	
	if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0){
		printf("Eroare de conectare la server");
		return 1;
	}

	printf("Connected\n");

	uint16_t l = 719;
	l = htons(l);

    send(c, &l, sizeof(l), 0);

	// l = htons(l);

	// send(c, &cerinta, 719 * sizeof(char), 0);

	char respnse[1001];


	recv(c, &l, sizeof(l) , MSG_WAITALL);
	l = htons(l);

	printf("%hu", l);

	uint16_t num;
	recv(c, &num, sizeof(num), MSG_WAITALL);
	num = ntohs(num);

	recv(c, respnse, num * sizeof(char) , MSG_WAITALL);


	printf("%s\n", respnse);


	close(c);
}

/*
Serverul asteapta apoi un numar care reprezinta lungimea enuntului. 
Serverul se comporta apoi ca un magazin de carti. 
Clientul se comporta ca un "display" pentru server, si afiseaza meniul trimis de server (care e de fapt un sir de caractere).
Pentru interactiunea cu serverul, clientul trebuie sa trimita caractere, siruri de caractere, sau alte date cerute. 
Serverul este implementat "gresit" (are o eroare de logica). 
Scopul vostru este sa abuzati de acest lucru pentru a cumpara cartea cu numele "Flag" pentru nota maxima. 
Serverul ruleaza pe o masina Little Endian si foloseste numere de tip "float" pentru a comunica numerele din aplicatie. S
erverul are deja un user numit "admin"*/