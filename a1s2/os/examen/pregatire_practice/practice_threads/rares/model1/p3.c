#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barr;
int nr[80000], minim  = INT_MAX, n, fr[50], sum = 0;


void* reader(void* arg)
{ int fd = open("./file.bin", O_RDONLY);
  for( int i = 0; i < n ; i ++)
     read(fd, &nr[i], 1);

  close(fd);
  return NULL;

}


void* work(void* arg){
 int index = (int)arg;
 int number = (index + 2) * 5;

 for(int i = 0; i < n; i ++)
    if( nr[i] == number)
      fr[index]++;

 printf("Nr %d - frecv: %d\n", number, fr[index]);
 pthread_mutex_lock(&mtx);
 sum += fr[index];
 pthread_mutex_unlock(&mtx);

 pthread_barrier_wait(&barr);

 pthread_mutex_lock(&mtx);

 int media = sum/50;
 if(abs(media - fr[index]) < minim)
     minim = abs(media- fr[index]);

 pthread_mutex_unlock(&mtx);

 pthread_barrier_wait(&barr);

 if( abs(media - fr[index]) == minim)
   printf("Numarul %d\n", number);

free(arg);
return NULL;}

int main(int argc, char** argv){

  if(argc != 2 ){printf("nr incorect de arg"); exit(1);}

  n = atoi(argv[1]);

   pthread_t rdr;
   pthread_create(&rdr, NULL, reader, NULL);
   pthread_join(rdr, NULL);

  pthread_t tid[50];
  pthread_barrier_init(&barr,NULL, 50);

  for ( int i = 0; i < 50 ; i ++){
     int* a = malloc(sizeof(int));
         *a = i;
      pthread_create(&tid[i], NULL, work, a);}


  for( int i = 0; i <50 ; i ++)
   pthread_join(tid[i], NULL);

 printf("Media frecventelor este: %d\n", (sum/50));

 pthread_barrier_destroy(&barr);

 return 0;
}