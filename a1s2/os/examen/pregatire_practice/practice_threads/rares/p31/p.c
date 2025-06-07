#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int flag = 0;
pthread_barrier_t barr;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;;

void* generate() {

	pthread_barrier_wait(&barr);
	while(1) {
		pthread_mutex_lock(&mtx);
		if(flag == 0) {
			int nr = rand() % 111112;
			printf("Generated: %d\n",nr);
			if(nr % 1001 == 0) {
				flag = 1;
				break;
			}
		} else {
			break;
		}
		pthread_mutex_unlock(&mtx);
	}
	pthread_mutex_unlock(&mtx);
	return NULL;
}

int main(int argc, char** argv) {


	srand(time(NULL));
	if(argc != 2) {
		perror("Usage: ./p [integer]");
		exit(1);
	}
	int n = atoi(argv[1]);
	
	pthread_barrier_init(&barr,NULL,n);
	
	pthread_t th[n];

	for(int i = 0; i < n; ++i) {
		pthread_create(&th[i],NULL,&generate,NULL);
	}

	for(int i = 0; i < n; ++i) {
		pthread_join(th[i],NULL);
	}

	pthread_barrier_destroy(&barr);

	return 0;
}
