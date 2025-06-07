#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define MAX_SIZE 101

int main() {
	int fr = open("fifo_req",O_RDONLY);
	while(1) {
		char str[MAX_SIZE], rez[MAX_SIZE];
		read(fr,str,MAX_SIZE * sizeof(char));
		printf("S Input: %s\n", str + 1);
		char voc = str[0];
		int poz = 0;
		for( int i = 0; i < strlen(str); ++i)
			if( str[i] != voc) 
				rez[poz++] = str[i];	
		rez[poz] = '\0';
		printf("S Output: %s\n", rez);
		int fw = open("fifo_res",O_WRONLY);
		write(fw,rez,MAX_SIZE * sizeof(char));
		close(fw);
	}
}
