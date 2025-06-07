#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <fcntl.h>



int main() {
	int fr,fw,r;
	fw = open("req",O_WRONLY);
	fr = open("res",O_RDONLY);
	r = rand() % 10 + 1;
	write(fw,&r,sizeof(int));
	printf("start: SENT %d\n",r);
	while(1) {
		read(fr,&r,sizeof(int));
                printf("1st RECEIVED %d\n",r);
                if(r == -1) {
                        printf("1st FINISHED\n");
                }
                if(r == 10) {
                        printf("2nd WINS\n");
                        r = -1;
                        write(fw,&r,sizeof(int));
                        break;
                }
                int k = rand() % 10 + 1;
		k = rand() % 100;
                write(fw,&k,sizeof(int));
		printf("1st SENT %d\n",k);
	}
	close(fr);
	close(fw);
	return 0;
}
