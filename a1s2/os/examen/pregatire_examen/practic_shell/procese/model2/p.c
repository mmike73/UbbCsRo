#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>

int produs_cifre(int n) {
	int p = 1;
	while(n) {
		p *= (n % 10);
		n /= 10;
	}
	return p;
}

int suma_cifre(int n) {
	int s = 0;
	while(n) {
		s += (n % 10);
		n /= 10;
	}
	return s;
}

int main(int argc, char** argv) {
	srand(time(NULL));
	int status, fd[2];
	status = pipe(fd);

	if(status < 0) {
		perror("pipe()");
		exit(1);
	}

	int pid1 = fork();

	if(pid1 < 0) {
		perror("fork()");
		exit(1);
	} else if( pid1 == 0) {
		close(fd[0]);
		int n, k;

		while(1) {
			n = rand() % 100;
			printf("Introdu un numar: ");
			scanf("%d", &k);
			
			write(fd[1],&n,sizeof(int));
			write(fd[1],&k,sizeof(int));
			if(k == -1) break;
		}

		close(fd[1]);
		exit(0);
	}

	int pid2 = fork();
	
	if( pid2 < 0) {
		perror("fork()");
		exit(1);
	} else if( pid2 == 0) {
		close(fd[1]);
		int n, k;
		FILE* file = fopen("rez", "w");

		while(1) {
			read(fd[0],&n,sizeof(int));
			read(fd[0],&k,sizeof(int));
			
			if(k == -1) break;
			else if(k % 2 == 1) {
				int suma = suma_cifre(n);
				fprintf(file,"%d Suma: %d\n",n,suma);
			} else {
				int produs = produs_cifre(n);
				fprintf(file,"%d Produs: %d\n", n, produs);
			}
		}

		fclose(file);
		close(fd[0]);
		exit(0);
	}

	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
	return 0;
}
