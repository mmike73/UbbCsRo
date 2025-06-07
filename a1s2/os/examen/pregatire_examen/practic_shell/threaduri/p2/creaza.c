#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

int main( int argc, char** argv) {
	srand(time(NULL));
	int fd = open("numere", O_WRONLY | O_CREAT);
	for( int i = 1; i < 70000; ++i) {
		write(fd,&i, 1);
	}
	close(fd);
	return 0;
}
	
