//
// Created by Mihai Moldovan on 05.03.2024.
//
#include <stdio.h>

int ind_nr_div(int a[], int numar) {
    for( int i = 1; i <= numar; i++) a[i] = 0;
    int aux = numar, d = 2;
    a[1] = 1;
    if( numar % 2 == 0)
        for( int i = 2; i < numar; ++i)
            if( i % d == 0) a[i]++;
    while( aux > 1) {
        if( aux % d == 0) {
            while( aux % d == 0) aux /= d;
            for( int i = d + 1; i < numar; ++i)
                if( i % d == 0) a[i]++;
        }
        d ++;
    }
}