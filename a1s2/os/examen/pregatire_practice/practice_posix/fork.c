#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
	fork();
	if( fork()) {
		fork();
	}
	printf("hello\n");
}
