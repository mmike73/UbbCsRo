#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <pthread.h>

int N, NT;
int *ciur;
int *cnt_prime;
int *num;
int average;

pthread_t rt;
pthread_t* th;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

pthread_barrier_t barr;

void* citeste(void* arg) {
	int fd = open("numere", O_RDONLY);
	for(int i = 0; i < N; ++i) {
		read(fd,&num[i],1);
	}
	close(fd);
	return NULL;
}

int creeaza_ciur() {
	int cnt_prime = 0;
	
	for( int i = 0; i < 128; ++i) ciur[i] = 0;
	ciur[0] = 1;
	ciur[1] = 1;
	int d = 2;
	while( d * d <= 128) {
		if(ciur[d] == 0) {
			int c = 2;
			while(d * c < 128) {
				ciur[d * c] = 1;
				c ++;
			}
		}
		d++;
	}

	for( int i = 0; i < 128; ++i) 
		if(ciur[i] == 0) cnt_prime ++;

	return cnt_prime;
}
	
void* count(void* arg) {
	int nr = *(int*)arg;
	free(arg);
	for( int i  = 0; i < N; ++i) {
		printf("%d ===== %d \n", num[i], nr);
		if( num[i] == nr) {
			cnt_prime[nr] ++;
		}
	}
	pthread_barrier_wait(&barr);

	int sum = 0, cnt = 0;
	for( int i = 0; i < 100; ++i) {
		sum += cnt_prime[i] * i;
		cnt += cnt_prime[i];
	}
	if( nr < 100) {
		pthread_mutex_lock(&mtx);
		average = sum / cnt;
		pthread_mutex_unlock(&mtx);
		printf("%d cnt: %d av: %d\n", nr, cnt_prime[nr] , average);
	}
	return NULL;
}

int main(int argc, char** argv) {
	printf("Introdu un numar (50000, 80000 sau 100000): ");
       	scanf("%d", &N);
	
	num = malloc(N * sizeof(int));
	ciur = malloc(128 * sizeof(int));
	cnt_prime = malloc(128 * sizeof(int));

	NT = creeaza_ciur();
	
	pthread_create(&rt, NULL, &citeste, NULL);
	
	pthread_barrier_init(&barr, NULL, NT);

	int p = 0;
	th = malloc(NT * sizeof(pthread_t));
	for(int i = 0; i < 128; ++i) {
		if( ciur[i] == 0) {
			int* ind = malloc(sizeof(int));
			*ind = i;
			pthread_create(&th[p++], NULL, &count, ind);
		}
	}

	for( int i = 0; i < NT; ++i) {
		pthread_join(th[i], NULL);
	}

	int difmin = 1000000000;
	for( int i = 0; i < 128; ++i) {
		if( ciur[i] == 0) {
			if(abs(average - cnt_prime[i]) < difmin) difmin = abs(average - cnt_prime[i]);
		}
	}

	for( int i = 0; i < 128; ++i) {
		if(difmin == abs(cnt_prime[i] - average)) printf("%d - %d aparitii\n", i, cnt_prime[i]);
	}
	
	free(ciur);
	free(num);
	free(cnt_prime);
	return 0;

