//
// Created by Mihai Moldovan on 02.03.2024.
//
#include <stdio.h>
/**
 * in tabloul bidimensiuonal triangle se formeaza triunghiul lui pascal pentru m dat
 * (cu m coloane)
 * @param triangle - matrice 101 x 101
 * @param m - max 101 - numarul de linii, combinari de cate elemente am nevoie
 */
int pascal_triangle(int triangle[][101], int m) {
        triangle[0][0] = 1;
    for( int i = 1; i <= m; ++i) {
        triangle[i][0] = 1;
        for( int j = 1; j <= i; j ++)
            triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
    }
    return 0;
}
