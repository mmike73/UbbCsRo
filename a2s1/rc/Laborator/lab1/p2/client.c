#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h> 
int main() {
  int c;
  struct sockaddr_in server;
  uint16_t nr_spatii;
  uint16_t length;
  char* text = malloc(100);

  c = socket(AF_INET, SOCK_STREAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(57575);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("192.168.64.25");
  
  if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la conectarea la server\n");
    return 1;
  }
  
  printf("text = ");
  fgets(text, 100, stdin) ;
  length =strlen(text);
  length = htons(length);
  send(c, &length, sizeof(uint16_t), 0);
  length = ntohs(length);
  send(c, text, length * sizeof(char), 0);
  recv(c, &nr_spatii, sizeof(nr_spatii), 0);
  nr_spatii = ntohs(nr_spatii);
  printf("Numarul de spatii: %d\n", nr_spatii);
  close(c);
  free(text);
}
