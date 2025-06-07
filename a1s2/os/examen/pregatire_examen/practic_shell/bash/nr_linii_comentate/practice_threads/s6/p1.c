#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>

#define MAX_THR 100
#define MAX_NUM 100000

int suma = 0;
int numere[MAX_NUM];

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

//thread start routine
void* do_work(void* arg) {
	int id = *(int*)arg;
	free(arg);

	int st = id * (MAX_NUM / MAX_THR);
	int dr = st + (MAX_NUM / MAX_THR);
	
	//daca imbrac forul in mutex, threadul curent va pastra mutexul fara sa fie i executie
	//so va bloca tot
	for( int i = st; i < dr; ++i) {
		pthread_mutex_lock(&mtx);
		suma += numere[i];

		pthread_mutex_unlock(&mtx);
	}
	
	printf("Suma: %d\n",suma);

	return NULL;
}

int main(int argc, char**argv) {

	srand(time(NULL));
	for( int i = 0; i < MAX_NUM;++i) {
		numere[i] = rand() % 10;
	}

	//make 100 threads
	//identificatorii threadurilor
	pthread_t tid[MAX_THR];

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

	//un thread are propria - stiva
	//			- marea parte a datelor
	//			- contextul de exxecutie (valorile din registri)
	


	return 0;
}
