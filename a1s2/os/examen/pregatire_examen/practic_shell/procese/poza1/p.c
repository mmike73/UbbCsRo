#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
//#include <sys/
#include <time.h>

int sumcif(int n) {
	int rez = 0;
	while(n) {
		rez += n % 10;
		n /= 10;
	}
	return rez;
}

int prodcif(int n) {
	int rez = 1;
	while(n) {
		rez *= (n % 10);
		n /= 10;
	}
	return rez;	
}

int main(int argc, char** argv) {
	srand(time(NULL));
	int pd[2];
	int status = pipe(pd);
	if(status < 0) {
		perror("pipe(pd)");
		exit(1);
	}

	int pid1 = fork();
	 if(pid1 < 0) {
                perror("pipe()");
                exit(1);
        } else if( pid1 == 0) {
                close(pd[0]);
		
		int k,n;
		while(1) {
			printf("Introdu un numar: ");
			scanf("%d",&k);

			n = rand() % 10000;

			write(pd[1],&k,sizeof(int));
			if(k == 0) {
				break;
			}
			write(pd[1],&n,sizeof(int));
		}
                close(pd[1]);
                exit(0);
        }

	int pid2 = fork();

	if(pid2 < 0) {
		perror("pipe()");
		exit(1);
	} else if( pid2 == 0) {
		close(pd[1]);
		
		FILE* fd = fopen("operatii","w");
		
		int n, k;
		while(1) {
			read(pd[0],&k,sizeof(int));
			read(pd[0],&n,sizeof(int));
			
			int rez;
			if(k == 0) {
				break;
			} else if(k % 2 == 0) {
				rez = sumcif(n);

			} else {
				rez = prodcif(n);
			}	
		
			fprintf(fd,"%d %d %d\n", k, n, rez);
		}
		fclose(fd);
		close(pd[0]);
		exit(0);
	}

	close(pd[1]);
	close(pd[0]);

	wait(NULL);
	wait(NULL);
	return 0;
}
