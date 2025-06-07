#include <stdio.h

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

int** mat;
int n, m;

void* aduna_linie(void* a) {
	int sum = 0, line = *(int*)a;
	free(a);
	for(int i = 0; i < m; ++i) {
		sum += mat[line][i];
	}
	printf("Thread apelat %d - suma %d\n", line, sum);
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

	pthread_t td[n];
	for(int i = 1; i <= n; ++i) {
		int*p = malloc(sizeof(int));;
		*p = i;
		if(0 != pthread_create(&td[i-1],NULL,&aduna_linie,p)) {
			perror("pthread_create");
			exit(1);
		}
	}

	for(int i = 1; i <= n; ++i) {
		pthread_join(td[i-1],NULL);
	}

	for(int i = 0; i < n;++i)
                free(mat[i]);
	free(mat);	
	return 0;
}
