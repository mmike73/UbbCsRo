#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main() {
	char sir[] = "abcdefghijklmnopqrstuvwxyza";	
	char vocale[] = "aeiou";

	for( int i = 0; i < 5; ++i) {	

		int ok = fork();
		if(ok == -1) {
			perror("fork()");
			exit(EXIT_FAILURE);
		}
		if(ok == 0) {
			printf("Elimina %c\n",vocale[i]);
			for( int j = 0; j <= strlen(sir); ++j)
				if(sir[j] == vocale[i]) {
					char tmp[strlen(sir)];
					strcpy(tmp,sir + j + 1);
					strcpy(sir + j, tmp);

				}

			printf("%s\n",sir);
			
			int fr = open("f1",O_RDONLY);
			int fw = open("f1",O_WRONLY);
			if(fw == -1) {
				perror("open('f1', O_WRONLY)");
				exit(EXIT_FAILURE);
			}
			write(fw,sir,strlen(sir) * sizeof(char));
			printf("%d\n",(int)strlen(sir));
			close(fw);
			close(fr);
			exit(0);
		}
		
		int fr = open("f1",O_RDONLY);
		if (fr < 0)
		{
			perror("open()");
			exit(EXIT_FAILURE);
		}
		
		char tmp[100];
		read(fr, tmp, 100);
		printf("Citit: %s\n", tmp);
		
		close(fr);
		wait(NULL);
	}

	return 0;
}

