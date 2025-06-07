#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>

#define MAX_THR 50
#define MAX_NUM 100000

int sum_min = 0;
int numere[MAX_NUM];

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t bar;


//thread start routine
void* do_work(void* arg) {
	int id = *(int*)arg;
	free(arg);
	
	int min = INT_MAX;
	int st = id * (MAX_NUM / MAX_THR);
	int dr = st + (MAX_NUM / MAX_THR);
	
	//daca imbrac forul in mutex, threadul curent va pastra mutexul fara sa fie i executie
	//so va bloca tot
	for( int i = st; i < dr; ++i) {
		if(numere[i] < min) 
			min = numere[i];
	
	}
	//suma val minime
	pthread_mutex_lock(&mtx);
	sum_min += min;
	pthread_mutex_unlock(&mtx);
	
	//pentru ca trebuie ca toate procesele sa isi termine calculele
	//pun bariera
	
	pthread_barrier_wait(&bar);		

	float medie = sum_min / MAX_THR;

	//calc diferenta absoluta
	int dif = abs(medie - min);

	printf("[Thread %2d] Medie: %f Diferenta: %d Minim: %d\n",id,medie,dif,min);

	//distroy barrier

	return NULL;
}

int main(int argc, char**argv) {

	srand(time(NULL));
	for( int i = 0; i < MAX_NUM;++i) {
		numere[i] = rand();
	}

	//make 100 threads
	//identificatorii threadurilor
	pthread_t tid[MAX_THR];
	
	pthread_barrier_init(&bar, NULL, MAX_THR);

	for( int i = 0; i < MAX_THR; ++i) {
		// do_dork e thread tart routine
		int *p = malloc(sizeof(int));
		*p = i;
		if(pthread_create(&tid[i], NULL, do_work, p) != 0) {
			perror("Pthread_Create()");
			exit(1);	
		}
	}

	//astept terminarea threadurilor
	for( int i = 0; i < MAX_THR; ++i) {
		//fara &
		pthread_join(tid[i],NULL);
	}
	
	pthread_barrier_destroy(&bar);

	//un thread are propria - stiva
	//			- marea parte a datelor
	//			- contextul de exxecutie (valorile din registri)
	return 0;
}
