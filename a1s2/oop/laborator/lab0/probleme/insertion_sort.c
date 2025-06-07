//
// Created by Mihai Moldovan on 28.02.2024.
//
#include <stdio.h>

void insertion_sort(int n, int a[]) {
    int cmp, j;
    for( int i = 2; i <= n; i++) {
        cmp = a[i];
        j = i - 1;
        while(j >= 1 && a[j] > cmp) {
            a[j + 1] = a[j];
            j --;
        }
        a[j + 1] = cmp;
    }
}
