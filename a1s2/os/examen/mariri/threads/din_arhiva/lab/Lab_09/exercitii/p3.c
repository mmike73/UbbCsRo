#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char** argv) {
	char litere[] = "abcdefgjijklmnopqrstuvwxyz";

	for( int i = 0; i < strlen(litere); ++i) {
		

		int pid = fork();

		if( pid == -1) {
			perror("fork()");
			exit(1);
		}
		if( pid == 0) {
			FILE* fd = fopen("text.txt","r");

			if(fd == NULL) {
				perror("fopen()");
				exit(1);
			}
			char ch;
			int frecv = 0;
			while((ch = fgetc(fd))>0) {
				if( ch == litere[i]) {
					frecv++;
				}
			}
			printf("Litera %c, fregv %d\n", litere[i], frecv);
			fclose(fd);
			exit(0);
		}
		wait(NULL);
	}
	
	return 0;
}
