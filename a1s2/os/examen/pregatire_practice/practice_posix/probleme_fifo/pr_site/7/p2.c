#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <fcntl.h>

int main() {
	int fr,fw,r;
        fr = open("req",O_RDONLY);
	fw = open("res",O_WRONLY);
	while(1) {
		read(fr,&r,sizeof(int));
		printf("2nd RECEIVED %d\n",r);
		if(r == -1) {
			printf("2nd FINISHED\n");
		}	
		if(r == 10) {
			printf("1st WINS\n");
			r = -1;
			write(fw,&r,sizeof(int));
			break;
		}
		int k = rand() % 10 + 1;
		k = rand() % 17;
		write(fw,&k,sizeof(int));
		printf("2nd SENT %d\n",k);
	}
	close(fr);
	close(fw);
	return 0;
}
