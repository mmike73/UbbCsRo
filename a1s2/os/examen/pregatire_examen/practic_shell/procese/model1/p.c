#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char** argv) {
	srand(time(0));
	int pd[2];
	int status = pipe(pd);

	if(status < 0) {
		perror("pipe()");
		exit(1);
	}

	int pid1 = fork();
	if(pid1 == 0) {
		close(pd[0]);
		while( 1) {
		
		int a = rand() % 101;
		int b = rand() % 101 + 1;
		
		char sym;
		int ok = 0;
		while(!ok) {
			printf("Introdu * / sau 0: ");
			scanf(" %c",&sym);
			if(sym == '*' || sym == '/' || sym == '0') {
				ok = 1;
			} else {
				printf("Se accepta doar * / sau 0\n");
			}
		}
		write(pd[1],&a,sizeof(int));
		write(pd[1],&b,sizeof(int));
		write(pd[1],&sym,sizeof(char));
		printf("[A]: sent %d %c %d\n", a, sym, b);
		if( sym == '0') break;
		}
		close(pd[1]);
		exit(0);
	} else if( pid1 < 0) {
		perror("fork()");
		exit(1);
	}

	int pid2 = fork();
	if(pid2 == 0) {
		close(pd[1]);
		FILE* fd = fopen("rez","w");
		int a, b;
		char sym;
		while(1) {
			read(pd[0],&a,sizeof(int));
			read(pd[0],&b,sizeof(int));
			read(pd[0],&sym,sizeof(char));
			printf("[B]: received %d %c %d\n", a, sym, b);
			if(sym == '*') fprintf(fd,"%d\n",a*b);
			else if(sym == '/') fprintf(fd,"%d\n",a/b);
			else break;
		}		
		close(pd[0]);
		exit(0);
	} else if(pid2 < 0) {
		perror("fork()");
		exit(1);
	}

	close(pd[0]);
	close(pd[1]);
	wait(NULL);
	wait(NULL);
	return 0;
}
