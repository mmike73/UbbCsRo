#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int n;
	if(argc < 2 || ((n = atoi(argv[1])) <= 0)) {
		fprintf(stderr,"Usage: ./p [numar_procese]\n");
		return 0;
	}

	printf("PARINTE PID: %d\n",getpid());

	for( int i = 0; i < n; ++i) {
		int pid = fork();
		if(pid == 0) {
			printf("COPIL PID: %d  PPID: %d \n",getpid(), getppid());
			exit(0);
		}
		printf("PARINTE PID_COPIL: %d\n", pid);
	}
	for( int i = 0; i < n; ++i) wait(NULL);

	return 0;

}
