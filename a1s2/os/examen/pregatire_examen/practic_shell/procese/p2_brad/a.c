#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#define NF 101

int cmmdc(int n, int m) {
	if(m == 0) return n;
	if(n > m) cmmdc(m, n % m);
	if(n <= m) cmmdc(n, m % n);
}

int main(int argc, char** argv) {
	int a, b;
	printf("Introdu 2 numere: ");
	scanf("%d %d", &a, &b);
	printf("Introdu numele FIFO-ului: ");
	char* nf = malloc(NF * sizeof(char));
	scanf("%s",nf);
	
	mkfifo(nf,0777);
	
	int fd = open(nf, O_WRONLY);
	int mc = cmmdc(a,b);
	write(fd,&mc,sizeof(int));

	free(nf);
	return 0;
}
