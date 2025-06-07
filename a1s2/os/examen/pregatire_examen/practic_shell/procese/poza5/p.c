#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
	srand(time(NULL));

	int pid1 = fork();
	if(pid1 < 0) {
		perror("fork()");
		exit(1);
	} else if(pid1 == 0) {
		mkfifo("numere",0777);
		printf("[C1]: a creat FIFO-ul numere\n");
		
		int fd = open("numere", O_RDONLY);
		printf("[C1]: a deschis FIFO-ul numere\n");
;
		int fr = open("raspuns", O_WRONLY);
		printf("[C1]: a deschis FIFO-ul raspuns\n");

		int X = rand() % 9001 + 1000; 
		printf("[C1]: numarul cautat este %d\n", X);

		int rec = 0;
		char gt = '>' , lt = '<', eq = '=';

		while(rec != X) {
			read(fd,&rec,sizeof(int));
			printf("[C1]: a citit din FIFO-ul numere %d\n", rec);
			if(rec < X) {
				write(fr,&lt,sizeof(char));
				printf("[C1]: a scris in FIFO-ul raspuns %c\n", lt);

			} else if(rec > X) {
				write(fr,&gt,sizeof(char));
				printf("[C1]: a scris in FIFO-ul raspuns %c\n", gt);
			} else {
				write(fr,&eq,sizeof(char));
				printf("[C1]: a scris in FIFO-ul raspuns %c\n", eq);
			}
		}

		close(fr);
		unlink("numere");
		close(fd);
		exit(0);
	}

	int pid2 = fork();
	if(pid2 < 0) {
		perror("fork()");
		exit(1);
	} else if( pid2 == 0) {
		int fd = open("numere",O_WRONLY);
		printf("[C2]: a deschis FIFO-ul numere\n");

		mkfifo("raspuns",0777);
		printf("[C2]: a creeat FIFO-ul raspuns\n");

		int fr = open("raspuns",O_RDONLY);
		printf("[C2]: a deschis FIFO-ul raspuns\n");
		
		char sig = ' ';
		int gen;

		while(sig != '=') {
			gen = rand() % 9001 + 1000;
			write(fd,&gen,sizeof(int));
			printf("[C2]: a scris in FIFO-ul numere %d\n", gen);
			read(fr,&sig,sizeof(char));	
			printf("[C2]: a citit din FIFO-ul raspuns %c\n",sig);
		}
	
		
		close(fr);
		close(fd);
		unlink("raspuns");
		exit(0);
	}
	wait(NULL);
	wait(NULL);
	return 0;
}
