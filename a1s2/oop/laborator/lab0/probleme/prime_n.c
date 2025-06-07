//
// Created by Mihai Moldovan on 28.02.2024.
//
#include <stdio.h>

int genereaza_n_prime(int a[], int n) {
    int cnt = 0;
    int ciur[1001] = {0};
    ciur[0] = 1;
    ciur[1] = 1;
    for(int i = 2; i * i <= 1001, cnt < n; i += 1) {
        if( ciur[i] == 0) {
            a[cnt++] = i;
            int d = 2;
            while (i * d <= 1000) {
                ciur[i * d] = 1;
                d++;
            }
        }
    }
    return cnt;
}

int genereaza_prime_ltn(int a[], int n) {
    //
    int cnt = 0;
    int ciur[1001] = {0};
    ciur[0] = 1;
    ciur[1] = 1;
    for(int i = 2; i  <= n; i += 1) {
        if( ciur[i] == 0) {
            a[cnt++] = i;
            int d = 2;
            while (i * d <= n) {
                ciur[i * d] = 1;
                d++;
            }
        }
    }
    return cnt;
}