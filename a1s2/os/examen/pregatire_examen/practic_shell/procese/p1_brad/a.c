#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#define NF 101
#define NC 10001

int main(int argc, char** argv) {
	char* nume_fis = malloc(NF*sizeof(char));
	printf("Introdu un nume de fisier: ");
	scanf("%s", nume_fis);
	int* cif = malloc(NC * sizeof(int));
	FILE* fd_cif = fopen(nume_fis, "r");
	int i = 0;
	while(fscanf(fd_cif,"%d",&cif[i]) == 1) {
		printf("%d \n", cif[i]);
		i++;
	}
	printf("%d numere\n",i);
	fclose(fd_cif);

	mkfifo("numere", 0777);
	int fd = open("numere", O_WRONLY);
	write(fd,cif,i * sizeof(int));
	
	//?
	close(fd);

	free(nume_fis);
	free(cif);
	return 0;
}
