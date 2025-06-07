#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

struct res {
	int nr_litere, nr_cifre, nr_caractere_speciale;
} res;

void* count(void* arg) {
	char* word = (char*)arg;
	//printf("Pentru '%s' avem %ld caractere.\n",word,strlen(word));
	
	struct res* result = malloc(sizeof(res));;
	result->nr_litere = 0;
	result->nr_cifre = 0;
	result->nr_caractere_speciale = 0;	
	
	for(int i = 0; i < strlen(word);++i) {
		if(('a' <= word[i] && word[i] <= 'z') || ('A' <= word[i] && word[i] <= 'Z')) result->nr_litere++;
		else if('0' <= word[i] && word[i] <= '9') result->nr_cifre++;
		else result->nr_caractere_speciale++;		
	}

	free(arg);
	return (void**)result;
}

int main(int argc, char** argv) {
	if(argc <= 1) {
		perror("Usage: ./p [string1] [string2] ...");
		exit(1);
	}
	
	pthread_t th[argc];
	for(int i = 1; i < argc;++i) {
		char* p = malloc(sizeof(char) * strlen(argv[i]));
		strcpy(p,argv[i]);
		if(pthread_create(&th[i],NULL,&count,p) != 0) {
			perror("Failed to create thread!");
		}
	}
	void* result;
	int total_l = 0, total_c = 0, total_s = 0;
	for(int i = 1; i < argc; ++i) {
		if(pthread_join(th[i],&result) != 0) {
			perror("Faled to join thread!");
		}
		struct res R = *(struct res*)result;
		free(result);
		total_l += R.nr_litere;
		total_c += R.nr_cifre;
		total_s += R.nr_caractere_speciale;
		printf("R: %d %d %d\n",R.nr_litere, R.nr_cifre, R.nr_caractere_speciale);
	}
	printf("GT: %d litere %d cifre %d speciale\n",total_l,total_c,total_s); 
	return 0;
}
