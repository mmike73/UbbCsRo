#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>

int main(int argc, char** argv) {
	if(argc == 1) {
		printf("Usage: ./p command arg1 arg2");
		exit(0);
	}

	struct timeval tv1,tv2;
	gettimeofday(&tv1,NULL);
	int f = fork();


	if( f == -1) {
		perror("fork()");
		exit(0);
	}
	if(f == 0) {
		if(execvp(argv[1], argv + 1) == -1) {
			perror("Error running the given command.");
			exit(1);
		}	
		exit(0);
	}
	wait(0);
	gettimeofday(&tv2,NULL);
	printf("Total time: %f seconds\n", (double)(tv2.tv_usec-tv1.tv_usec) / 1000000 + (double)(tv2.tv_sec - tv1.tv_sec));
	return 0;
}
