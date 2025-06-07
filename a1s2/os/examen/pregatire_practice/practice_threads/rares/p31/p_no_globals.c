#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

typedef struct data {
	int* flag;
	pthread_barrier_t* barr;
	pthread_mutex_t* mtx;
} data;

void* generate(void* arg) {
	struct data td = *(struct data*)arg;	
	pthread_barrier_wait(td.barr);
	while(1) {
	pthread_mutex_lock(td.mtx);
		if(td.flag == 0) {
			int nr = rand() % 111112;
			printf("Generated: %d\n",nr);
			if(nr % 1001 == 0) {
				flag = 1;
				break;
			}
		} else {
			break;
		}
		pthread_mutex_unlock(&td.mtx);
	}
	pthread_mutex_unlock(td.mtx);
	return NULL;
}

int main(int argc, char** argv) {
	int* flg = malloc(sizeof(int));
	pthread_barrier_t *ba = malloc(sizeof(pthread_battier_t));
	pthread_mutex_t *mt = malloc(sizeof(pthread_mutex_t));


	srand(time(NULL));
	if(argc != 2) {
		perror("Usage: ./p [integer]");
		exit(1);
	}
	int n = atoi(argv[1]);

	*flg = 0;
	pthread_barrier_create(*ba,NULL,n);
	pthread_mutex_create(*mtx);
	
	struct data *args = malloc(n * sizeof(data));
	
	pthread_barrier_init(*ba,NULL,n);
	
	pthread_t th[n];

	for(int i = 0; i < n; ++i) {
		args[i].mtx = mtx;
		args[i].flag = flg;
		args[i].barr = ba;	
		pthread_create(&th[i],NULL,&generate,&args[i]);
	}

	for(int i = 0; i < n; ++i) {
		pthread_join(th[i],NULL);
	}

	pthread_barrier_destroy(*ba);

	return 0;
}
