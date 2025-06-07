//
// Created by Mihai Moldovan on 28.02.2024.
//
#include <stdio.h>

int calc_sum() {
    int n, x = 0, sum = 0;
    scanf("%d", &n);
    for( int i = 1; i <= n; ++i) {
        scanf("%d", &x);
        sum += x;
    }
    return sum;
}

int zecimale( int a[], float rap, int n) {
    for( int i = 1; i <= n; ++i) {
        rap = rap * 10;
        a[i] = (int)rap % 10;
    }
    return 0;
}