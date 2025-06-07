#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void f(int n) {
	if( n > 0) {
		int pid = fork();
		if( pid < 0) {
			perror("fork() error");
			exit(1);
		}
		if( pid == 0) {
			printf("COPIL PID: %d  PPID: %d \n",getpid(), getppid());
			f(n - 1);
		}
	}
	wait(NULL);
	exit(0);
}

int main(int argc, char** argv) {
	int n;
	if( argc != 2 || ((n = atoi(argv[1])) <= 0)) {
		fprintf(stderr, "Usage: ./p [numar_procese]");
		return 0;
	}

	f(n);
	return 0;
}	
