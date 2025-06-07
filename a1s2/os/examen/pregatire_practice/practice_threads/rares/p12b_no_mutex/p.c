#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

int** mat;
int n, m;
int total = 0;
int* rez;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* aduna_linie(void* a) {
	int sum = 0, line = *(int*)a;
	free(a);
	//pthread_mutex_lock(&mtx);
	for(int i = 0; i < m; ++i) {
		sum += mat[line][i];
	}
	//pthread_mutex_unlock(&mtx);
	printf("Thread apelat %d - suma %d\n", line, sum);
	rez[line - 1] = sum;
	return NULL;
}
		
int main(int argc,char** argv) {
	
	FILE* fd = fopen("test", "r");
	if(fd < 0) {
		perror("open()");
		exit(1);
	}
	fscanf(fd,"%d",&n);
	fscanf(fd,"%d",&m);
	printf("%d %d\n",n,m);
	
	
	mat = (int**)malloc(n*sizeof(int*));
        for(int i = 0; i < n;++i) {
		mat[i] = (int*)malloc(m*sizeof(int));
	}

        for( int i = 0; i < n;++i)
                for( int j = 0; j < m; ++j) {
                        fscanf(fd,"%d",&mat[i][j]);
                }
	
	rez = (int*)malloc(n*sizeof(int));

	pthread_t td[n];
	for(int i = 0; i < 9000; ++i) {
		int*p = malloc(sizeof(int));;
		*p = i + 1;
		if(0 != pthread_create(&td[i],NULL,&aduna_linie,p)) {
			perror("pthread_create");
			exit(1);
		}
	}
	
	int suma_totala = 0;;
	for(int i = 0; i < 9000; ++i) {
		pthread_join(td[i],NULL);
		suma_totala += rez[i];
	}

	for(int i = 0; i < n;++i)
                free(mat[i]);

	printf("Total: %d\n",suma_totala);
	free(mat);
	free(rez);
	pthread_mutex_destroy(&mtx);	
	return 0;
}
