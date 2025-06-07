#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
 
int main() {
  int s;
  struct sockaddr_in server, client;
  int c, l;
  
  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    printf("Eroare la crearea socketului server\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(57575);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  
  if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la bind\n");
    return 1;
  }
 
  listen(s, 5);
  
  l = sizeof(client);
  memset(&client, 0, sizeof(client));
  
  while (1) {
    char* text = malloc(100);
    uint16_t length, nr_spatii = 0;
    c = accept(s, (struct sockaddr *) &client, &l);
    printf("S-a conectat un client.\n");
    // deservirea clientului
    recv(c, &length, sizeof(length), MSG_WAITALL);
    length = ntohs(length);

    printf("%d\n", length);

    recv(c, text, length * sizeof(char), MSG_WAITALL);
    
    nr_spatii = 0;
    
    for (int i = 0; i < length; ++i) {
	if (text[i] == ' ') nr_spatii++;
    }

    nr_spatii = ntohs(nr_spatii);
    
    send(c, &nr_spatii, sizeof(nr_spatii), 0);
    free(text);
    close(c);
  }
}
