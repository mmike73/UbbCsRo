#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int fd[2];
	int ps = pipe(fd);

	if(ps == -1) {
		perror("pipe(fd)");
		exit(EXIT_FAILURE);
	}

	int nr;
	printf("Introdu un numar:");
	scanf("%d", &nr);
	write(fd[1],&nr,sizeof(int));

	close(fd[1]);	

	int pid = fork();
	if(pid == -1) {
		perror("fork()");
		exit(EXIT_FAILURE);
	}

	if(pid == 0) {
		int num;
		read(fd[0],&num,sizeof(int));
		close(fd[0]);
		if( num == 0) {
			printf("Numarul %d este prim\n", num);
			exit(0);
		}
		if( num < 2 || num % 2 == 0) {
			printf("Numarul %d nu este prim\n", num);
			exit(0);
		}
		for( int i = 3; i * i <= num; i += 2)
			if(num % i == 0) {
				printf("Numarul %d nu este prim\n", num);
                        	exit(0);
			}
		printf("Numarul %d este prim\n", num);
                exit(0);
	}
	int status;
	wait(&status);
	printf("Copil incheiat cu statusul %d\n", status);
	close(fd[0]);
	return 0;
}
