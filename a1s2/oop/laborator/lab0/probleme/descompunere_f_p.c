//
// Created by Mihai Moldovan on 29.02.2024.
//
#include <stdio.h>

int descompunere_f_p(int n, int a[], int b[]) {
    int d = 2, cnt = 0, exp;
    while ( n > 1) {
        exp = 0;

        if( n % d == 0) {
            cnt ++;
            a[cnt] = d;
            while(n % d == 0) {
                n /= d;
                exp ++;
            }
            b[cnt] = exp;
        }
        d += 1;
        if( d * d > n && n != 1) {
            cnt ++;
            a[cnt] = n;
            b[cnt] = 1;
        }
    }
    return cnt;
}

int not_prim(int n) {
    if(n < 2) return 1;
    if( n == 2) return 0;
    if( n % 2 == 0) return 1;
    for( int i = 3; i * i <= n; i += 2)
        if( n % i == 0) return 1;
    return 0;
}

int suma_nre_prime(int n, int a[]) {
    if( n % 2 == 1) {
        return -1;
    }
    a[0] = a[1] = n / 2;
    while( a[0] >= 2 && a[1] < n && ( not_prim(a[0]) || not_prim(a[1]) )) {
        a[0]--;
        a[1]++;
    }
    return 1;
}