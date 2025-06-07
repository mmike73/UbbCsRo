#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

int N;
int *NRS;
int sum;
int NZO;
pthread_t th[50];
pthread_t tr;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barr;

void* citeste(void* arg) {
	int fd = open("numere",O_RDONLY);
	for(int i = 0; i < N; ++i) {
		read(fd,&NRS[i],1);
	}
	close(fd);
	return NULL;
}

void* work(void* arg) {
	int ind = *(int*)arg;
	free(arg);

	f

	return NULL;
}

int main(int argc, char** argv) {	
	printf("Introdu un numar (50000,60000,80000): ");
	scanf("%d",&N);
	
	NRS = malloc(N * sizeof(int));

	pthread_create(&tr,NULL,&citeste,NULL);
	pthread_join(tr,NULL);

	pthread_barrier_init(&barr,NULL,50);
	
	//for(int i = 0; i < N; ++i) printf("%d\n",NRS[i]);
	int* ind;
	for(int i = 0; i < 50; ++i) {
		ind = malloc(sizeof(int));
		*ind = i;
		pthread_create(&th[i],NULL,&work,ind);
	}

	for(int i = 0; i < 50; ++i) {
		pthread_join(th[i],NULL);
	}

	pthread_mutex_destroy(&mtx);
	pthread_barrier_destroy(&barr);

	free(NRS);
	return 0;

}
