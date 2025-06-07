#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int prim(int n) {
	if( n < 2) return 0;
	if(n == 2) return 1;
	if(n % 2 == 0) return 0;
       	for( int i = 3; i < n; i += 2)
		if(n % i == 0)
			return 0;	
	return 1;
}	

int main(int argc, char** argv) {
	int fd[2];
	int status = pipe(fd);
	if(status != 0) {
		perror("pipe(fd)");
		exit(EXIT_FAILURE);
	}
	int pid = fork();
	if(pid == 0) {
		close(fd[1]);
		int nr;
		read(fd[0],&nr,sizeof(int));
		if(prim(nr)) printf("%d este prim\n" ,nr);
		else printf("%d NU este prim\n",nr);

		exit(0);
	} else if(pid < 0) {
		perror("fork()");
		exit(1);
	} else {
		close(fd[0]);
		int nr;
		printf("Introdu un numar: ");
		scanf("%d",&nr);
		write(fd[1],&nr, sizeof(int));
		close(fd[0]);
	}
	wait(NULL);
}
