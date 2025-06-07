#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#define MAX_SIZE 101

int main() {
	char sir[MAX_SIZE] = "abefijopuv";
	char* tmp = (char*)malloc(strlen(sir)*sizeof(char));
	char voc[] = "aeiou";

	for( int i = 0; i < 5; ++i) {
		
		int ok = fork();
		if( ok == -1) {
			perror("fork()");
			exit(EXIT_FAILURE);
		}
		if( ok == 0) {
			for( int j = 0; j < strlen(sir); ++j)
				if(sir[j] == voc[i]) {
					char temp[strlen(sir)];
					strcpy(temp, sir+j+1);
					strcpy(sir+j, temp);
				}

			int fw = open("f1",O_WRONLY);
			if( fw == -1) {
				perror("open(f1)");
				exit(EXIT_FAILURE);
			}
			write(fw,sir,MAX_SIZE * sizeof(char));
			close(fw);
			exit(0);
		}
		wait(NULL);
		
		int fr = open("f1",O_RDONLY);
		read(fr,sir,MAX_SIZE*sizeof(char));
		close(fr);
	}

	printf("%s\n", sir);

	free(tmp);
	return 0;
}
