#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
	int fd[2];
	int status = pipe(fd);
	if(status != 0) {
		perror("pipe()");
		exit(EXIT_FAILURE);
	}
	
	if(fork() == 0) {
		close(fd[1]);
		int rec;
		read(fd[0],&rec,sizeof(int));
		if(rec % 2) printf("[C] %d este impar\n", rec);
		else printf("[C] %d este par\n",rec);
		close(fd[0]);
		exit(0);
	} else {
		close(fd[0]);
		int send;
		printf("[P] Introdu un numar: ");
		scanf("%d", &send);
		write(fd[1],&send,sizeof(int));
		close(fd[1]);
		wait(NULL);
	}
	return 0;
}
