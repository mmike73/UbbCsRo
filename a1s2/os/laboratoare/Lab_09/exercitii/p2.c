#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char**argv) {
	int n = 10;


	for( int i = 2; i < n / 2; ++i) {
		int pid = fork();
		if( pid == -1) {
			perror("fork()");
			exit(1);
		}
		if( pid == 0) {
			FILE* file = fopen("test.txt","r");
			if( file == NULL) {
				perror("fopen()");
				exit(1);
			}
			FILE* tmp = fopen("test.txt","w");
                        if( tmp == NULL) {
                                perror("fopen()");
                                exit(1);
                        }
			int nr;
			while( fscanf(file,"%d",&nr) > 0) {
				if( nr % i != 0 || nr == i) {
					fprintf(tmp, "%d ",nr);	
				}
				fclose(file);
				fclose(tmp);
				remove("test.txt");
				rename("tmp.txt","test.txt");
				exit(0);
			}
			wait(NULL);
		}
	}

	return 0;
}
