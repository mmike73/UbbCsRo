#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

int frecv[10];
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* count_and_change(void* arg) {
	char* nr = (char*)arg;
	for(int c = 0; c < 10; ++c) {
		int cnt = 0;
		for(int i = 0; i < strlen(nr);i++) {
			if(nr[i] == '0' + c) cnt++;
		}
		pthread_mutex_lock(&mtx);
		frecv[c] += cnt;
		pthread_mutex_unlock(&mtx);
	}
	free(arg);
	return NULL;
}

int main(int argc, char** argv) {
	if(argc <= 1) {
		perror("Usage: ./p [decimal number1] [decimal number 2]");
		exit(1);
	}

	pthread_t th[argc];
	for(int i = 1; i < argc; ++i) {
		char* nr = malloc(strlen(argv[i]) * sizeof(char));
		strcpy(nr,argv[i]);
		if(pthread_create(&th[i],NULL,&count_and_change,(void*)nr) != 0)
			perror("Thread couldn't be created!");
	}

	for(int i = 1; i < argc;++i) {
		if(pthread_join(th[i],NULL) != 0)
			perror("Thread couldn't be joined!");
	}
	pthread_mutex_destroy(&mtx);
	
	for(int i = 0; i < 10; ++i) {
		printf("%c a aparut de %d ori\n",'0'+i,frecv[i]);
	}

	return 0;
}
