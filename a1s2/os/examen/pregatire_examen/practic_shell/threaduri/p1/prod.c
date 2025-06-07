#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {
	srand(time(NULL));
	int fd = open("numere",O_WRONLY);
	for(int i = 0; i < 50000; ++i) {
	       	int nr  =  rand() % 128;
		write(fd,&nr,1);
	}
	close(fd);
	return 0;
}
