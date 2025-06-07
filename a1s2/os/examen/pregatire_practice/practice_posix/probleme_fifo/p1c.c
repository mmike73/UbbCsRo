#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main() {
    char sir[] = "abcdefghijklmnopqrstuvwxyza";
    char vocale[] = "aeiou";

    // Open the named pipe for reading
    int fr = open("f1", O_RDONLY);
    if (fr == -1) {
        perror("open('f1', O_RDONLY)");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 5; ++i) {
        int ok = fork();
        if (ok == -1) {
            perror("fork()");
            exit(EXIT_FAILURE);
        }
        if (ok == 0) {
            printf("Elimina %c\n", vocale[i]);
            for (int j = 0; j <= strlen(sir); ++j)
                if (sir[j] == vocale[i]) {
                    memmove(&sir[j], &sir[j + 1], strlen(sir) - j);
                    break;
                }

            printf("%s\n", sir);

            int fw = open("f1", O_WRONLY);
            if (fw == -1) {
                perror("open('f1', O_WRONLY)");
                exit(EXIT_FAILURE);
            }
            write(fw, sir, strlen(sir) * sizeof(char));
            close(fw);
            exit(EXIT_SUCCESS);
        }
    }

    // Wait for all child processes to complete
    for (int i = 0; i < 5; ++i) {
        wait(NULL);
    }

    // Read the final result from the named pipe
    char crt = '0';
    int poz = 0;
    lseek(fr, 0, SEEK_SET); // Reset file offset to the beginning
    while (read(fr, &crt, sizeof(char)) > 0 && crt != '\0') {
        sir[poz++] = crt;
    }
    close(fr);

    printf("Final: %s\n", sir);

    return 0;
}
    
