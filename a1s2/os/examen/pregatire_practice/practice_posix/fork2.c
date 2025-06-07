#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
int main() {
	signal(SIGCHLD,SIG_IGN);
	printf("START: pid=%d ppid=%d\n", getpid(), getppid());
	int i = -2, j = -2, k = -2;
	i = fork();
	if(j = fork()) {
		k = fork();
	}
	printf("Hello pid=%d ppid=%d i=%d j=%d k=%d\n", getpid(),getppid(),i,j,k);
}
