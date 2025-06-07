#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
struct data {
  int nr;
  int tries;
};
 
int getIdFromCookie() {
  char *cookie = getenv("HTTP_COOKIE");
  int id = -1;
  //printf("Cookie: %s;", cookie);
  if (cookie != NULL) {
      sscanf(cookie, "gameid=%d", &id);
  }
  return id;  
}
 
int getNumberFromQueryString() {
  char buffer[2048];
  int id, nr;
  strcpy(buffer, getenv("QUERY_STRING"));
  printf("Buffer: %s<br>",buffer);
  sscanf(buffer, "nr=%d", &nr);
  printf("From form got: %d<br>", nr);
  return nr;  
}
 
int init() { 
  int r, id;
  int code;
  char filename[100];
  struct data d;
  
  srand(time(NULL) ^ getpid());
  r = rand() % 100;

  //printf("Starting game with number: %d<br>", r);
  mkdir("./tmp", 0700);
  do {
    id = rand();
    //printf("Trying new user with id: %d<br>", id);
    sprintf(filename, "./tmp/%d.txt", id);
    code = creat(filename, O_CREAT | O_EXCL | 0600);
    //printf("New file with status: %d<br>", code);
  }
  while (code < 0);
 
  d.nr = r;
  d.tries = 0;
  //printf("Writing to the new file: Number: %d; Tries: %d)", d.nr, d.tries);
  write(code, &d, sizeof(d));
  close(code);
  //printf("Written and closed file<br>");
  return id;
}
 
void destroy(int id) {
  printf("Set-Cookie: gameid=deleted; Path=/; Expires=Thu, 01 Jan 1970 00:00:00 GMT\r\n");
  char filename[100];
  sprintf(filename, "./tmp/%d.txt", id);
  unlink(filename);
}
 
int getNumberFromFile(int id) {
  char filename[100];
  int fd;
   
  sprintf(filename, "./tmp/%d.txt", id);
  struct data d;
  
  printf("Opening file %d.txt<br>", id);
  fd = open(filename, O_RDWR);
  if (fd < 0)
    return -1;
  printf("File oppened successfully with desriptor: %d<br>", fd);
  read(fd, &d, sizeof(d));
  d.tries++;
  printf("Read from file: Number: %d; Current tries: %d; <br>", d.nr, d.tries);
  lseek(fd, 0, SEEK_SET);
  printf("Line after lseek(fd, 0, SEEK_LET)<br>");
  write(fd, &d, sizeof(d));  
  printf("Written to file.<br>");
  close(fd);
  return d.nr;
}
 
int getNoOfTries(int id) {
  char filename[100];
  int fd;
  printf("Getting number of tries for latest game: %d", id);
  sprintf(filename, "./tmp/%d.txt", id);
  struct data d;
  printf("Oppening file: %s<br>", filename);
  fd = open(filename, O_RDONLY);
  printf("Reading from file using descriptor: %d<br>", fd);
  read(fd, &d, sizeof(d));
  printf("Read data from file: Number: %d; Tries: %d", d.nr, d.tries);
  close(fd);
  return d.tries;    
}
 
int isNewUser() {
  char *cookie = getenv("HTTP_COOKIE");
  //printf("Cookie from isNewUser(%s)<br>", cookie);

  if (cookie == NULL || strstr(cookie, "gameid=") == NULL) {
     //printf("Cookie is null. Creating a new user.<br>");
     return 1;	  
  }
  return 0;  
}
 
void printForm(int id) {
  printf("<form action='play.cgi' method='get'>\n");
  printf("Nr: <input type='text' name='nr'><br>\n");
  printf("<input type='submit' value='Trimite'>\n");
  printf("</form>");;
}
 
int main() {
  int id;
  int status;



  id = getIdFromCookie(); 
  char filename[1000];
  sprintf(filename, "./tmp/%d.txt", id);
  int fd = open(filename, O_RDWR);
  if (fd < 0 && !isNewUser()) {
	  printf("Set-Cookie: gameid=deleted; Path=/; Expires=Thu, 01 Jan 1970 00:00:00 GMT\r\n");
  }
  else if(fd >= 0) close(fd);
 

  if (isNewUser()) {
    id = init();    
    printf("Set-Cookie: gameid=%d; Path=/;\n", id);
    printf("Content-type: text/html\r\n\r\n");

    status = 0;
  } 
  else {
    printf("Content-type: text/html\r\n\r\n");
    int nr, nr2;
    id = getIdFromCookie(); 
    nr = getNumberFromQueryString();
    nr2 = getNumberFromFile(id);
    
    printf("Fromf file %d.txt, got: nr2:%d<br>From keyboard got: %d<br>", id, nr, nr2); 

    if (nr2 == -1)
      status = 1;
    else if (nr == nr2)
      status = 2;
    else if (nr < nr2)
      status = 3;
    else if (nr > nr2)
       status = 4;                
  }
  
  
  printf("<html>\n<body>\n");
  
  switch (status) {
    case 0 : printf("Ati inceput un joc nou.<br>\n"); printForm(id); break;
    case 1 : printf("Eroare. Click <a href='play.cgi'>here</a> for a new game!"); break;
    case 2 : printf("Ati ghicit din %d incercari. Click <a href='play.cgi'>here</a> for a new game!</body></html>", getNoOfTries(id)); destroy(id); break;
    case 3 : printf("Prea mic!<br>\n"); printForm(id); break;
    case 4 : printf("Prea mare!<br>\n"); printForm(id);
  }
  
  printf("</body>\n</html>");
}
