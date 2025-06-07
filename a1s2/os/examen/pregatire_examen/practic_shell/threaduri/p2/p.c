#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <limits.h>
#include <fcntl.h>

int N;
int* NUM;
int CIF[10];
int sum;
int cea_mai_apropiata = 2000000000;

pthread_t th[10];
pthread_t tr;
int minim = 2000000000, avg;

pthread_barrier_t barr1,barr2;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* read_all(void* arg) {
	int fd = open("numere", O_RDONLY);
	NUM = malloc(N * sizeof(int));
	for(int i = 0; i < N; ++i)
		read(fd,&NUM[i],1);
	close(fd);
	return NULL;
}

void* count(void* arg) {
	int cif = *(int*)arg;
	free(arg);
	
	for( int i = 0; i < N; ++i) {
		if(NUM[i] % 10 == cif) CIF[cif]++;
	}
	
	pthread_barrier_wait(&barr1);

	pthread_mutex_lock(&mtx);
	sum += CIF[cif];
	pthread_mutex_unlock(&mtx);

	pthread_barrier_wait(&barr2);
	
	pthread_mutex_lock(&mtx);
	avg = sum / 10;
	if(abs(avg - CIF[cif]) < cea_mai_apropiata) {
		cea_mai_apropiata = abs(avg - CIF[cif]);
	}
	pthread_mutex_unlock(&mtx);
	
	return NULL;
}

int main(int argc, char** argv) {
	pthread_barrier_init(&barr1,NULL,10);
	pthread_barrier_init(&barr2,NULL,10);
	printf("Introdu un numar 40000/60000/70000: ");
	scanf("%d",&N);
	
	pthread_create(&tr,NULL,&read_all,NULL);
	pthread_join(tr,NULL);

	for(int i = 0; i < 10; ++i) {
		int* cifra = malloc(sizeof(int));
		*cifra = i;
		pthread_create(&th[i],NULL,&count,cifra);
	
	}

	for(int i = 0; i < 10; ++i) {
		pthread_join(th[i],NULL);
	}

	for(int i = 0; i < 10; ++i) {
		printf("Aparitii cu %d cifre: %d\n", i, CIF[i]);
	}
	printf("Media este: %d\n", avg);
	printf("Cea mai apropiata: %d\n", cea_mai_apropiata);
	
	for(int i = 0; i < 10; ++i) {
		if( abs(CIF[i] - avg) == cea_mai_apropiata)
			printf("%d e la distanta %d de medie\n", i, cea_mai_apropiata);
	}

	free(NUM);
	pthread_mutex_destroy(&mtx);
	pthread_barrier_destroy(&barr1);
	pthread_barrier_destroy(&barr2);
	return 0;
}
