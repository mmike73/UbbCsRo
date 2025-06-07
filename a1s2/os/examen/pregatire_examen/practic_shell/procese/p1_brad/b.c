#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#define NC 10001
#define NF 101

int main(int argc, char** argv) {
	int pd[2];
       	int status = pipe(pd);
	if(status != 0) {
		perror("pipe(pd)");
		exit(1);
	}
	
	int pid1 = fork();
	if(pid1 == 0) {
		close(pd[0]);
		int* cif = malloc(NC * sizeof(int));
		int fd = open("numere", O_RDONLY);
	
		int non = read(fd,cif,sizeof(int) * NC);
		non /= 4;
		int total = 0;
		for(int i = 0; i < non; ++i)
			total += cif[i];
		write(pd[1],&total,sizeof(int));
		close(fd);
		close(pd[1]);
		unlink("numere");
		free(cif);
		exit(0);	
	}
	int pid2 = fork();
	if(pid2 == 0) {
		close(pd[1]);
		int nr;
		read(pd[0],&nr,sizeof(int));

		int d = 1;
		while(d * d < nr) {
			if(nr % d == 0) {
				printf("%d %d ", d, nr / d);
			}
			d++;
		}
		if( d * d == nr) {
			printf("%d\n", d);
		} else printf("\n");

		close(pd[0]);
		exit(0);
	}
	wait(NULL);
	wait(NULL);
	return 0;
}
