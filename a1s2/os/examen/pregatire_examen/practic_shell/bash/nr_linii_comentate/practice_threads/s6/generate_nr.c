#include <stdio.h>

int main() {
	FILE* fd = fopen("numere","w");
	for( int i = 1; i <= 100000; ++i) {
		fprintf(fd,"%d ",i);
	}
	fclose(fd);
}
