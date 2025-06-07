//
// Created by Mihai Moldovan on 05.03.2024.
//
#include <stdio.h>

int ind_euler(int euler[], int numar) {
    for( int i = 1; i <= numar; ++i)
        euler[i] = i;
    for( int i = 2; i <= numar; ++i)
        if( euler[i] == i) {
            euler[i] --;
            for( int j = 2; j * i <= numar; ++j)
                euler[j * i] /= i * ( i - 1);
        }
}