#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX_SIZE 101

int exista(int x, int a[]) {
	int i = 0;
	while(a[i] != 0) {
		if(a[i] == x) return 1;
		i++;
	}
	return 0;
}

int main() {
	int a[MAX_SIZE], n = 0;
	FILE* fd = fopen("numere","r");
	while(fscanf(fd,"%d",&a[n]) != -1) {
		n++;
	}
	a[n] = 0;
	close(fd);
	int N = a[n - 1];	
	int fw = open("req",O_WRONLY);
	for( int i = 2; i * i <= N; ++i) {
		if(exista(i,a)) {
			n = 0;
			while(a[n] != 0) ++n;
			a[n + 1] = i;
			N = a[n - 1];
			write(fw,&a,MAX_SIZE * sizeof(int));
		
			int fr = open("res",O_RDONLY);
			read(fr,&a,MAX_SIZE * sizeof(int));
			close(fr);
		}
	}
	int p = 0;
	printf("Numerele prime sunt:\n");
	while(a[p] != 0)
		printf("%d ",a[p++]);

	close(fw);
	return 0;
}
