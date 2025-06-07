#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <math.h>

#define NR_THR 10

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barr;

int *arr;
int size;
int even[101];

void *routine(void *arg) {
        int tid = *((int *) arg);
        free(arg);

        int left = size / NR_THR * tid;
        int right = size / NR_THR * (tid + 1);

        for (int i = left; i < right; i++) {
                if (arr[i] % 2 == 0 && arr[i] >= 2 && arr[i] <= 100) {
                        pthread_mutex_lock(&mtx);
                        even[arr[i]]++;
                        pthread_mutex_unlock(&mtx);
                }
        }

        pthread_barrier_wait(&barr);

        double avg = 0.0;
        for (int i = 2; i <= 100; i += 2) {
                avg += even[i];
        }
        avg /= 50;

        printf("[THREAD %d] Calculated average -> %f\n", tid, avg);

        double minDiff = 100.000;
        for (int i = 2; i <= 100; i += 2) {
                if (fabs(even[i] - avg) < minDiff) {
                        minDiff = fabs(even[i] - avg);
                }
        }
        printf("[THREAD %d] Calculated minimum difference -> %f\n", tid, minDiff);

        pthread_barrier_wait(&barr);

        if (tid == 0) {
                for (int i = 2; i <= 100; i += 2) {
                        if (fabs(even[i] - avg) == minDiff) {
                                printf("%d ", i);
                        }
                }
                printf("\n");
        }

        return NULL;
}

int main(int argc, char **argv) {
        if (argc != 2) {
                printf("[ERROR] Invalid number of arguments...\n");
                printf("[USAGE] $1 <int>\n");
                exit(1);
        }

        size = atoi(argv[1]);
        arr = malloc(size * sizeof(int));
        memset(arr, 0, size * sizeof(int));
        pthread_barrier_init(&barr, NULL, NR_THR);

        FILE *file = fopen("data.bin", "rb");

        fread(arr, sizeof(int), size, file);
        fclose(file);

        pthread_t tids[NR_THR];
        for (int i = 0; i < NR_THR; i++) {
                int *temp = malloc(sizeof(int));
                *temp = i;
                pthread_create(&tids[i], NULL, routine, temp);
        }

        for (int i = 0; i < NR_THR; i++) {
                pthread_join(tids[i], NULL);
        }

        pthread_barrier_destroy(&barr);
        free(arr);

        return 0;
}