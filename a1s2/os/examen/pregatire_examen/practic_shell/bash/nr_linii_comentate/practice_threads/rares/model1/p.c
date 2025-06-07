#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>

int* numere;
int n = 0;
int rez[52];
int sum;

pthread_mutex_t mtx;
pthread_barrier_t mtx;

void* proceseaza(void* arg) {
	int id = *((int*)arg);
	free(arg);
	int sum_loc = 0;
	for(int i = id * 10; i < (id + 1) * 10; ++i) {
		if(numere[i] % 5 == 0) {
			sum_loc += numere[i];
			pthread_mutex_lock(&mtx[numere[i] / 5]);
			rez[numere[i] / 5]++;
			pthread_mutex_unlock(&mtx[numere[i] / 5]);
		}
	}

	return NULL;
}

int main(int argc, char** argv) {
	while(n != 90 && n != 100 && n != 110) {
		printf("Introdu un numar(90000 sau 100000 sau 170000):");
		scanf("%d",&n);
	}
	numere = malloc(n * sizeof(int));

	int fd = open("test_file",O_RDONLY);
	for(int i = 0; i < n; ++i) {
		numere[i] = 0;
		read(fd,&numere[i],8);
	}
	int *p;
	int nt = n / 10;

	pthread_mutex_init(&mtx, NULL);


	pthread_t th[10];
	for(int i = 0; i < nt; ++i) {
		p = (int*)malloc(sizeof(int));
		*p = i;
		if(pthread_create(&th[i],NULL,proceseaza,p) != 0) {
			perror("pthread_create()");
		}
	}

	for(int i = 0; i < nt; ++i) {
		if(pthread_join(th[i],NULL) != 0) {
			perror("pthread_join()");
		}
	}

	pthread_mutex_destroy(&mtx);

	free(numere);
	return 0;
}
