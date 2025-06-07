#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
	int fd[2]; //descriptori de fisiere
	int pres = pipe(fd);
	int numar;
	printf("Introdu un numar (parinte): ");
	scanf("%d",&numar);

	write(fd[1],&numar,sizeof(int));

	if(pres == -1) {
		perror("pipe()"); //aruncam eroarea
		exit(EXIT_FAILURE);
	}

	int pid = fork();
	if( pid == -1) {
		perror("fork()");
		exit(EXIT_FAILURE);
	}

	if(pid == 0) {
		printf("Child:\n");
		close(fd[1]); // closing write descriptor
		int nr;
		read(fd[0], &nr, sizeof(int));

		printf("Numarul extras (copil): %d.\n", nr);
		close(fd[0]);
		exit(0);
	}
	int status;
	wait(&status);
	printf("Copil incheiat cu status %d\n", status);
	close(fd[0]);
	close(fd[1]);
	return 0;
}
