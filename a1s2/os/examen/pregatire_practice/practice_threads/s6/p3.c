#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <fcntl.h>
#define BUF_SIZE 100
#define NR_THR 10

int fd;
int sum = 0;
int flag = 0; //1 - full buffer
int buffer[BUF_SIZE],ind = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;

void* consume(void* a) {
	pthread_mutex_lock(&mtx);
	while(flag == 0) {
		pthread_cond_wait(&cv,&mtx);
	}
	for(int i = 0; i < BUF_SIZE; ++i) {
		sum += buffer[i];
		printf("Added %d\n",buffer[i]);
	}
	ind = 0;
	pthread_mutex_unlock(&mtx);
	return NULL;
}

void* produce(void* a) {
	pthread_mutex_lock(&mtx);
	while(flag == 1) {
		pthread_cond_wait(&cv,&mtx);
	}
	while(ind < BUF_SIZE) {
		read(fd,&buffer[ind],sizeof(int));
		printf("Read %d\n",buffer[ind]);
		ind++;
	}
	flag = 1;
	pthread_cond_signal(&cv);
	pthread_mutex_unlock(&mtx);	
	return NULL;
}

int main(int argc, char** argv) {
	pthread_t tc[NR_THR], tp[NR_THR];
	fd = open("numere",O_RDONLY);

	if(fd == -1) {
		perror("open()");
		exit(0);
	}

	for(int i = 0; i < NR_THR; ++i) {
		int *k = (int*)malloc(sizeof(int));//identificatori ai threadurilor
		*k = i;
		pthread_create(&tp[i],NULL,consume,k);
		pthread_create(&tc[i],NULL,produce,k);
	}

	for(int i = 0; i < NR_THR; ++i) {
		pthread_join(tp[i],NULL);
		pthread_join(tc[i],NULL);
	}
	
	printf("SUMA: %d\n",sum);	
	return 0;
}
