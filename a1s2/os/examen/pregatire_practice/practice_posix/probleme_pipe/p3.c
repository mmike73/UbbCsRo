#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char** argv) {
	int fd[2];
	int st = pipe(fd);
	if( st == -1) {
		perror("pipefd");
		exit(EXIT_FAILURE);
	}

	char sir[101], car[2];
	int n;

	printf("Introdu un caracter: ");
	scanf("%s", car);
	getchar();
	printf("Introdu un sir de caractere: ");
	fgets(sir, 100, stdin);
	
	n = strlen(sir);

	write(fd[1],car,sizeof(char));
	write(fd[1],&n, sizeof(int));
	write(fd[1],sir,strlen(sir)*sizeof(char));
	
	close(fd[1]);

	st = fork();

	if(st == -1) {
		perror("fork()");
		exit(EXIT_FAILURE);
	}
	if(st == 0) {
		char caracter[2],sir[101];
		int nr;
		
		read(fd[0],caracter,sizeof(char));
		read(fd[0],&nr,sizeof(int));
		read(fd[0],sir,nr*sizeof(char));
		
		int cnt = 0;
		for( int i = 0; i < nr; ++i) {
			if( sir[i] == caracter[0])
				cnt++;
		}

		printf("Numarul de aparitii a %s este %d.\n", caracter, cnt);

		close(fd[0]);
		exit(0);
	}
	close(fd[0]);
	int status;
	wait(&status);

	printf("Copil incheiat cu status %d.\n", status);

	return 0;
}
