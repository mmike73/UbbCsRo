#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    int fd[2], out[2];
    int ok = pipe(fd);
    if( ok == -1) {
        perror("pipe(fd)");
        exit(EXIT_FAILURE);
    }
    ok = pipe(out);
    if( ok == -1) {
        perror("pipe(out)");
        exit(EXIT_FAILURE);
    }

    FILE* fin = fopen("f5.txt", "r");
    int a, b;
    fscanf(fin, "%d %d", &a, &b);

    write(fd[1],&a,sizeof(int));
    write(fd[1],&b,sizeof(int));
    close(fd[1]);
    ok = fork();
    if(ok == -1) {
        perror("fork()");
        exit(1);
    }
    if(ok == 0) {
        int sum = 0, term;
        read(fd[0],&term,sizeof(int));
        sum += term;
        read(fd[0],&term,sizeof(int));
        sum += term;
        close(fd[0]);
        write(out[1], &sum,sizeof(int));
        close(out[1]);
        close(out[0]);
        exit(0);
    }
    close(fd[0]);
    close(out[1]);
    int suma;
    read(out[0],&suma,sizeof(int));
    close(out[0]);
    printf("%d + %d = %d", a, b, suma);
    return 0;
}