#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mtx;
pthread_cond_t cv;
int fuel = 0;


void* fuel_filling(void* arg) {
	for(int i = 0; i < 5; ++i) {
		pthread_mutex_lock(&mtx);
		fuel += 15;
		printf("Filling station, quantity: %d\n",fuel);
		pthread_mutex_unlock(&mtx);
		pthread_cond_signal(&cv);
		sleep(1);
	}
	return NULL;
}

void* car(void* arg) {
	pthread_mutex_lock(&mtx);
	while(fuel < 40 ) {
		printf("Now fuel. Waiting...\n");
		pthread_cond_wait(&cv,&mtx);
	}
	fuel -= 40;
	printf("Got fuel, Left: %d\n",fuel);
	pthread_mutex_unlock(&mtx);
	return NULL;
}


int main(int argc, char** argv) {
	pthread_mutex_init(&mtx,NULL);
	pthread_cond_init(&cv,NULL);	
	pthread_t th[2];
	for(int i = 0; i < 2; ++i) {
		if(i == 1) {
			if(pthread_create(&th[i],NULL,&fuel_filling, NULL) != 0) {
				perror("Failed to create filler thread!");
			}
		} else {
			//prima data se creeaza masina
			if(pthread_create(&th[i], NULL,&car, NULL) != 0) {
				perror("Failed to create car thread!");
			}
		}
	}

	for(int i = 0; i < 2; ++i) {
		if(pthread_join(th[i],NULL) != 0) {
			perror("Failed to join thread!");
		}
	}
	pthread_mutex_destroy(&mtx);
	pthread_cond_destroy(&cv);
	return 0;
}
