#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#define STR_SIZE 1000
int main(int argc, char** argv) {
	int fd[2];
	int status = pipe(fd);
	if(status != 0) {
		perror("pipe(fd)");
		exit(1);
	}
	int pid = fork();
	if(pid < 0) {
		perror("fork()");
		exit(1);
	} else if( pid == 0) {
		close(fd[1]);
		char c;
		char text[STR_SIZE];
		read(fd[0],&c,sizeof(char));
		read(fd[0],&text,STR_SIZE * sizeof(char));
		close(fd[0]);
		int cnt = 0;
		for( int i = 0; i < strlen(text); i++) {
			if(text[i] == c) cnt++;
		}
		printf("%c are %d aparitii in %s\n",c,cnt,text);
		exit(0);
	}
	close(fd[0]);
	char c, text[STR_SIZE];
	printf("Introdu un caracter: ");
	scanf(" %c", &c);
	printf("Introdu un sir de caractere: ");
	getchar(); //pentru newline-ul de la sfarsitul liniei curente
	
	fgets(text, STR_SIZE, stdin);

	//scanf("%s", text);
	write(fd[1],&c, sizeof(char));
	write(fd[1],&text, STR_SIZE * sizeof(char));
	wait(NULL);
	return 0;
}
