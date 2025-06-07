#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 101

int main(int argc, char* argv[]) {
	char* str = (char*)malloc((strlen(argv[1]) + 1) * sizeof(char));
      	if(strlen(argv[1]) == 0) {
		printf("Call format: ./a [cuvant]\n");
		return 0;
	}	
	strcpy(str,argv[1]);
	
	char voc[] = "aAeEiIoOuU", req[101];
	
	int fw = open("fifo_req",O_WRONLY);
	for( int i = 0; i < 10; ++i) {
		printf("Input: %s\n", str);
		req[0] = voc[i];
		strcpy(req+1,str);
		write(fw,req,MAX_SIZE*sizeof(char));
		
		int fr = open("fifo_res",O_RDONLY);
		read(fr,str,MAX_SIZE*sizeof(char));
		close(fr);

		printf("Output: %s\n", str);
	}

	close(fw);
	free(str);
	return 0;
}
