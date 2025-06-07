#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#define NF 101

int main(int argc, char** argv) {
	int pd[2];
	int status = pipe(pd);

	if(status != 0) {
		perror("pipe()");
		exit(1);
	}
	int pid1 = fork();
	if(pid1 == 0) {
		close(pd[0]);
		char *nf = malloc(NF * sizeof(char));
		printf("Introdu numele FIFO-ului: ");
		scanf("%s",nf);

		int fd = open(nf, O_RDONLY);
		
		int nr;
		read(fd,&nr, sizeof(int));
		printf("%d\n",nr);
		unlink(nf);

		int d = 1;

		while(d * d < nr) {
			if( nr % d == 0) {
				int d2 = nr / d;
				write(pd[1],&d,sizeof(int));
				write(pd[1],&d2,sizeof(int));
			}
			d++;
		}
		if(d * d == nr) write(pd[1],&d,sizeof(int));
		
		free(nf);
		close(pd[1]);
		exit(0);
	} 

	int pid2 = fork();
	if(pid2 == 0) {
		close(pd[1]);
		int div;
		while( read(pd[0],&div,sizeof(int)) > 0) {
			printf("%d ",div);
		}
		printf("\n");
		close(pd[0]);
		exit(0);
	}
	close(pd[1]);
	close(pd[0]);
	wait(NULL);	
	wait(NULL);	
	return 0;
}
