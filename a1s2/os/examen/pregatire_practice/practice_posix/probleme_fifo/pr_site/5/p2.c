#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int boltz_criteria(int n) {
        if( n % 7 == 0) return 1;
        while( n > 0) {
                if( n % 10 == 7) return 1;
                n/=10;
        }
        return 0;
}

void play(int pipes[][2], int id, int n) {
        int nr = 1, i;

        int read_id = id % n;
        int write_id = (id + 1) % n;


	// inchide toate pipeurile de care nu e nevoie
	// e nevoie doar de cel care scrie urmatorului si cel care citeste din urmatorul
        for( i = 0; i < n; ++i) {
                if( i == read_id) {
                        close(pipes[i][1]);
                } else if( i == write_id) {
                        close(pipes[i][0]);
                } else {
                        close(pipes[i][0]);
                        close(pipes[i][1]);
                }
        }
	
	//tratarea cazului in care parintele incepe jocul
	if(id == 0) {
		printf("%d -start\n", nr);
		if(write(pipes[write_id][1],&nr,sizeof(int)) < 0) {
			perror("Error on writing number");
		}
	}

        while(nr >= 1) {
                if(0 > read(pipes[read_id][0], &nr, sizeof(int))) {
                        perror("Error reading number");
                }
                if( nr != 0) {
                        nr++;
                        int rez = random() % 3;

                        if(boltz_criteria(nr)) {
                                if(!rez) {
                                        printf("%d - GATA\n", nr);
                                        nr = 0;
                                } else {
                                        printf("BOLTZ!\n");
                                }
                        } else {
                                printf("%d\n", nr);
                        }

                        if( write(pipes[write_id][1], &nr, sizeof(int)) < 0) {
                                perror("Error writing number");
                        }
                } else {
                        if( write(pipes[write_id][1], &nr, sizeof(int)) < 0) {
                                perror("Error writing number");
                        }
                        break;
                }
        }
        wait(0);
        close(pipes[write_id][1]);
        close(pipes[read_id][0]);
}

int main(int argc, char** argv) {
        int N;
        if(argc < 2 || ((N = atoi(argv[1])) <= 0)) {
                perror("Usage: ./p [numar natural]");
                exit(1);
        }

        int fd[N][2], ok;

	//creeaza n pipeuri
	//n - 1 pricese daca numaram si procesul parinte, pipeuri care paseaza numarul de la un proces la altul
        for( int i = 0; i < N; ++i) {
                ok = pipe(fd[i]);
                if( ok != 0) {
                        perror("pipe()");
                        exit(1);
                }
        }

	//creeaza procesele (N la numar)
	//pricesul curent va fi i
        int i, f;
        for( i = 0; i < N; ++i) {
                f = fork();

                if(f < 0) {
                        perror("fork()");
                } else if(f > 0) {
                        break; //se vor crea procese din copiii
                } else {
                //va cicla mai departe
                }
        }
	
	//fiecare proces va apela procedura pley
        if( i < N)
                play(fd, i, N);
        //i va fi identificatorul copiilor
        return 0;

}
