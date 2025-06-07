#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char** argv) {
	int fd[2], status;
	status = pipe(fd);
	if(status != 0) {
		perror("pipe()");
		exit(1);
	}
	int pid = fork();
	if(pid < 0) {
		perror("fork()");
		exit(1);
	} else if( pid == 0) {
		close(fd[1]);
		int a, b;
		read(fd[0],&a,sizeof(int));
		read(fd[0],&b,sizeof(int));
		printf("Suma numerelor este: %d\n", a+b);
		close(fd[0]);
		exit(0);
	}
	close(fd[0]);
	printf("Introdu 2 numere: ");
	int a,b;
	scanf("%d %d", &a, &b);
	write(fd[1],&a,sizeof(int));
	write(fd[1],&b,sizeof(int));
	close(fd[1]);
	wait(NULL);
	return 0;
}
