#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int nr;
pthread_mutex_t mtx;
pthread_cond_t c_pare;
pthread_cond_t c_impare;

int* arr;
int nr_elem;

typedef struct data {
	int* array;
	int* nr_elem;
}data;

void* adauga_pare() {
	while(1) {
		pthread_mutex_lock(&mtx);
		if(nr_elem == 0) {
			int num = (rand() % 49) * 2;
                	arr[nr_elem++] = num;
			printf("[PAR]: Am scris %d\n",num);
		}
		if(nr_elem == nr) {
			pthread_mutex_unlock(&mtx);
			pthread_cond_signal(&c_pare);
			break;
		}
		while(arr[nr_elem - 1] % 2 == 0) {
			printf("[PAR]: Astept numar impar ...\n");
			pthread_cond_wait(&c_impare,&mtx);
		}
		if(nr_elem == nr) {
                        pthread_mutex_unlock(&mtx);
                        pthread_cond_signal(&c_pare);
                        break;
                }
		int num = (rand() % 49) * 2;
		arr[nr_elem++] = num;
		printf("[PAR]: Am scris %d\n",num);
		pthread_cond_signal(&c_pare);
		pthread_mutex_unlock(&mtx);
	}
	return NULL;
}

void* adauga_impare() {
	while(1) {
                pthread_mutex_lock(&mtx);
                if(nr_elem == 0) {
                        int num = (rand() % 49) * 2 + 1;
                        arr[nr_elem++] = num;
			printf("[IMPAR]: Am scris %d\n",num);
                }
		if(nr_elem == nr) {
                        pthread_mutex_unlock(&mtx);
                 	pthread_cond_signal(&c_impare);
		 	break;
                }
                while(arr[nr_elem - 1] % 2 == 1) {
                        printf("[IMPAR]: Astept numar par ...\n");
                        pthread_cond_wait(&c_pare,&mtx);
                }
		if(nr_elem == nr) {
                        pthread_mutex_unlock(&mtx);
			pthread_cond_signal(&c_impare);
                        break;
                }
                int num = (rand() % 49) * 2 + 1;
                arr[nr_elem++] = num;
		printf("[IMPAR]: Am scris %d\n",num);
                pthread_cond_signal(&c_impare);
                pthread_mutex_unlock(&mtx);
        }
        return NULL;
}


int main(int argc, char** argv) {
	srand(time(NULL));
	pthread_t th[2];
	if(argc != 2) {
		perror("Numar parametri invalid!");
		exit(1);
	}
	pthread_mutex_init(&mtx,NULL);
	pthread_cond_init(&c_pare,NULL);
	pthread_cond_init(&c_impare,NULL);
	
	nr = atoi(argv[1]);
	arr = malloc(nr*sizeof(int));
	
	if(pthread_create(&th[0],NULL,&adauga_pare,NULL) != 0) {
		perror("Thread couldn't be created");
	}
	if(pthread_create(&th[1],NULL,&adauga_impare,NULL) != 0) {
		perror("Thread could not be created");
	}

	if(pthread_join(th[0],NULL) != 0) {
                perror("Thread couldn't be joined");
        }
        if(pthread_join(th[1],NULL) != 0) {
                perror("Thread could not be joined");
        }
	pthread_cond_destroy(&c_pare);
	pthread_cond_destroy(&c_impare);
	pthread_mutex_destroy(&mtx);
	
	for(int i = 0; i < nr; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	free(arr);	

	return 0;
}
