#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char ** argv) {
	int p2c[2],c2p[2],ok;

	ok = pipe(p2c);
	if( ok == -1) {
		perror("pipr(p2c)");
		exit(EXIT_FAILURE);
	}
	
	ok = pipe(c2p);
	if( ok == -1) {
		perror("pipe(c2p)");
		exit(EXIT_FAILURE);
	}

	int a[3];
	printf("Introdu 2 numere: ");
	scanf("%d %d", &a[0],&a[1]);

	write(p2c[1],&a,2 * sizeof(int));

	close(p2c[1]);

	ok = fork();

	if( ok == -1) {
		perror("fork()");
		exit(EXIT_FAILURE);
	}
	if( ok == 0) {
		int t, sum = 0;
		
		read(p2c[0],&t,sizeof(int));
		sum+= t;

		read(p2c[0],&t,sizeof(int));
		sum+= t;
		
		printf("Suma in copil: %d.\n", sum);

		write(c2p[1],&sum,sizeof(int));

		close(c2p[0]);
		close(p2c[0]);
		close(c2p[1]);
		
		exit(EXIT_SUCCESS);
	}
	int s;
	read(c2p[0],&s,sizeof(int));
		
	printf("Suma este %d.\n", s);

	close(c2p[0]);
	close(p2c[1]);
	return 0;
}
