#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

int main(int argc, char** argv) {
	int N;
	if(argc < 2 || ((N=atoi(argv[1])) <= 0)) {
		perror("Usage: ./p [integer]");
		exit(1);
	}
	int p2c[2], c2p[2];
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
		int s = 0, n;
		close(p2c[1]);
		close(c2p[0]);
		for( int i = 0; i < N; ++i) {
			read(p2c[0],&n,sizeof(int));
			printf("received: %d\n",n);
			s += n;
		}
		close(p2c[0]);
		write(c2p[1],&s,sizeof(int));
		close(c2p[1]);
		exit(0);
	} else {
		int r;
		close(p2c[0]);
		close(c2p[1]);
		for( int i = 0; i < N; ++i) {
			r = rand() % 49;
			write(p2c[1],&r,sizeof(int));
			printf("sent: %d\n",r);
		}
		close(p2c[1]);
		read(c2p[0],&r,sizeof(int));
		close(c2p[0]);
		printf("suma: %d\n",r);
	}
	return 0;
}
