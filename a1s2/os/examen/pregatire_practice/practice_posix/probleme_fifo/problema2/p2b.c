#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX_SIZE 101

int main() {
	int fr = open("req",O_RDONLY);	
	int fw = open("res",O_WRONLY);
	int a[101], div;
	while(1) {
		read(fr,&a,MAX_SIZE * sizeof(int));
		int poz = 0;
		while(a[poz] != 0) {
			printf("%d ", a[poz]);
			poz++;
		}
		printf("\n");

		div = a[poz + 1];

		for( int i = 0; i <= poz; i++)
			if(a[i] % div == 0 && div != a[i]) {
				for( int j = i; j < poz;++j)
					a[j] = a[j + 1];
				poz--;
			}

		for( int i = 0; i < poz; ++i) {
			printf("%d ", a[i]);
		}
		printf("\n");

		write(fw,&a,MAX_SIZE * sizeof(int));
	}
	
	close(fw);
	close(fr);
	return 0;

}
