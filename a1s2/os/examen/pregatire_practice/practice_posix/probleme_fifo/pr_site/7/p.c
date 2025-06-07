#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

int main(int argc, char** argv) {
	int p2c[2],c2p[2];
	int ok = pipe(p2c);
	if(ok == -1) {
		perror("pipe(p2c)");
		exit(1);
	}
	ok = pipe(c2p);
	if(ok == -1) {
		perror("pipe(c2p)");
		exit(1);
	}
	
	int pid = fork();
	if(pid == -1) {
		perror("fork()");
		exit(1);
	} else if(pid == 0) {
		close(p2c[1]);
                close(c2p[0]);
		int n;
		while(1) {
			n = rand() % 4900;
			write(c2p[1], &n, sizeof(int));
			printf("C - SENT %d\n", n);
			read(p2c[0], &n, sizeof(int));
			printf("C - REC  %d\n", n);
			if(n == 10) {
				printf("C - PARRENT WON\n");
				kill(getppid(),SIGUSR2);
				break;
			}
		}	
		close(p2c[1]);
                close(c2p[0]);
		exit(0);
	} else {
		int n;
		close(p2c[0]);
		close(c2p[1]);
		while(1) {
			n = rand() % 4900;
			write(p2c[1], &n, sizeof(int));
                        printf("P - SENT %d\n", n);
                        read(c2p[0], &n, sizeof(int));
                        printf("P - REC  %d\n", n);
			if( n == 10) {
				printf("P - CHILD WON\n");
				kill(pid,SIGUSR1);
				break;
			}
		}
		wait(0);
		close(p2c[1]);
		close(c2p[0]);
	}
}

