#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
int main(int argc, char** argv) {

	int pd[2];
	int status = pipe(pd);

	if(status < 0) {	
		perror("pipe()");
		exit(1);
	}

	int pid1 = fork();
	
	if(pid1 < 0) {
		perror("fork()");
		exit(1);
	} else if(pid1 == 0) {
		close(pd[0]);
		FILE* fd = fopen("fisie_cuvinte","r");
		char c;
		char* s = malloc(101 * sizeof(char));

		while(fscanf(fd," %c %s",&c, s) > 0) {
			write(pd[1],&c,sizeof(char));
			write(pd[1],s,sizeof(char) * 101);
		}
		c = '0';
		write(pd[1],&c,sizeof(char));

		free(s);
		fclose(fd);
		close(pd[1]);
		exit(0);
	}


	int pid2 = fork();

	if(pid2 < 0) {
		perror("fork()");
		exit(1);
	} else if(pid2 == 0) {
		close(pd[1]);
		
		char c, *s = malloc(101 * sizeof(char));
		int poz = -1;
		while(read(pd[0],&c,sizeof(char))  > 0) {
			if(c == '0') break;
			read(pd[0],s,101*sizeof(char));
			poz = -1;
			for(int i = 0; i < strlen(s); ++i) {
				if(s[i] == c) {
					poz = i;
					break;
				}
			}

			printf("%c %s %d\n", c, s, poz);
		}
		free(s);	
		close(pd[0]);
		exit(0);
	}
	
	wait(NULL);
	wait(NULL);
	return 0;
}
