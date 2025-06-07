#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_SIZE 100

int main(int argc, char** argv) {
        int k = 0;
        char sir[] = "afoilwaensoifglhwlak";
        char vocale[] = "aAeEiIoOuU";
        char* tmp = (char*)malloc(MAX_SIZE*sizeof(char));

        for( int i=0; i < strlen(vocale); ++i) {

        int fd[2];
        int st = pipe(fd);

        if(st < 0) {
                perror("pipe(fd)");
                exit(1);
        }

        int pid = fork();

        if( pid == -1) {
                perror("fork()");
                exit(1);
        }

        if(pid == 0) {
                k = 0;
                close(fd[0]);
                for( int j = 0; j < strlen(sir);++j) {
                        if( sir[j] != vocale[i]) {
                                tmp[k++] = sir[j];
                        }
                }
                tmp[k] = '\0';
                write(fd[1],tmp,MAX_SIZE);
                close(fd[1]);
                exit(0);
        }
        close(fd[1]);
        read(fd[0],tmp,MAX_SIZE);
        strcpy(sir, tmp);
        wait(NULL);
        }
        printf("Sirul final: %s.\n",sir);

        return 0;
}
