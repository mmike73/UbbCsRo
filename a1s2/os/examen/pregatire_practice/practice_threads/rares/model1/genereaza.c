#include <stdio.h>
#include <fcntl.h>

int main() {
	int fd = open("test_file",O_WRONLY);
	int i;
	for(i = 1; i <= 90; ++i) {
		write(fd,&i,8);
	}
	return 0;
}
