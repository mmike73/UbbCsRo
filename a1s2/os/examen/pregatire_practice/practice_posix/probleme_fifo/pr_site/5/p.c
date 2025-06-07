/*
 * Joc de boltz:
 * N procese
 * incrementeaza un numar pornind de la 1
 * procesul 1 incrementeaza si trimite procesului 2, 2 la 3 etc
 * cand un proces ajunge la 7 sau multiplu de 7 se opreste si scrie BOLTZ
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int has_7(int n) {
	while(n) {
		if(n % 10 == 7) return 1;
		n/=10;
	}
	return 0;
}

int main(int argc, char**  argv) {
	int N;
	if( argc < 2 || ((N = atoi(argv[1])) <= 0)) {
		printf("Usage: ./p [numar intreg]");
		exit(1);
	}
	int i, fd[2];
	int ok = pipe(fd);
	if(ok == -1) {
		printf("pipe error\n");
		exit(0);
	}
	int start = 1;
	write(fd[0],&start,sizeof(int));
	while(1) {
	for( i = 1; i <= N; ++i) {
		int pid = fork();
		if( pid == -1) {
			perror("fork()");
			exit(1);
		} else if( pid == 0) {
			int s;
			read(fd[1],&s,sizeof(int));
			if(s % 7 == 0 && has_7(s)) {
				int r = rand();
				if( r % 3 == 0) {
					printf("Gata\n");
					exit(0);
				}
				printf("BOLTZ\n");
			} else {
				printf("%d\n", s);	
			}
			s++;
			write(fd[0],&s,sizeof(int));
			exit(0);
		}
	}
	}
	close(fd[1]);
	close(fd[0]);
	for( int i =  1; i <= N; ++i) wait(NULL);
	return 0;
}
