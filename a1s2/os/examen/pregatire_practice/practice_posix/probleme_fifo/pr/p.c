#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#define MAX_SIZE 101

int main(int argc, char** argv) {
	int n;
	char nume[101], buf[1001];
	
	printf("Introdu un numar: ");
	scanf("%d",&n);
	printf("Introdu un nume de fisier: ");
	scanf("%s",nume);
	FILE* fd = fopen(nume,"r");

	if(fd == NULL) {
		perror("fopen(nume,'r')");
		exit(1);
	}

	int p2c[2];
	int ok = pipe(p2c);

	if(ok == -1) {
		perror("pipe(p2c)");
		exit(1);
	}

	fscanf(fd,"%s",buf);

	write(p2c[1],buf,MAX_SIZE*sizeof(char));	
	printf("P SENT %s\n",buf);

	int f = fork();
	
	if(f == -1) {
		perror("fork()");
		exit(1);
	} else if(f == 0) {
		close(p2c[1]);
		char write_to_file[1001] = "";
		char cuvant[1101] = "";
		int cnt = 0;
		while(1) {
			read(p2c[0],buf,MAX_SIZE*sizeof(char));
			printf("C RECVD %s\n",buf);
                        if(buf[0] == '-' && buf[1] == '\0') {
				if(cnt % 2 == 0) {
					printf("Dati un cuvant de %d litere: ", n);
					scanf("%s",cuvant);
					strcat(cuvant," ");
					strcat(cuvant,write_to_file);
				}
				fclose(fd);
				FILE* fw = fopen(cuvant, "w");
				if(fw == NULL) {
					perror("fopen(name, 'w')");
					exit(1);
				}
				
				fprintf(fw,"%s",write_to_file);
				fclose(fw);
				exit(0);
			} else {
				strcat(write_to_file, " ");
				strcat(write_to_file, buf);
			}
			if(strlen(buf) == n) {
				cnt++;
                        }
			close(p2c[0]);
		}
	} else {
		close(p2c[0]);
		while(fscanf(fd,"%s",buf) != 0) {
                	write(p2c[1],buf,MAX_SIZE*sizeof(char));
			printf("P READ %s\n",buf);
        	}
		buf[0] = '-';
		buf[1] = '\0';
		write(p2c[1],&buf, MAX_SIZE*sizeof(char));
		printf("P SENT %s\n",buf);
		close(p2c[1]);		
	}


	return 0;
}
