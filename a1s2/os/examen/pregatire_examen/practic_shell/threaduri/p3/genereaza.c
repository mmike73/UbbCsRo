#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char**argv) {
	srand(time(NULL));

	int n;
	int fd = open("numere",O_WRONLY);
	for(int i = 0; i < 80000;++i) {
		n = rand() % 1000;
		write(fd,&n,1);
	}
	close(fd);

	return 0;
}
