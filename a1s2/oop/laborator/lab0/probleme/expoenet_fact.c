//
// Created by Mihai Moldovan on 02.03.2024.
//
#include <stdio.h>

/**
 *
 * @param n nunmar intreg
 * @param prim numar intreg prim
 * @return ecponentul la care se alfa numarul prim im scierea numarului n!
 */
int exponent_p_fact(int n, int prim) {
    int exp = 0;
    for( int i = 2; i <= n; i++) {
        int aux = i;
        while( aux % prim == 0) {
            exp ++;
            aux /= prim;
        }
    }
    return exp;
}

/**
 * @param a - lista cu n elemente de numere intregi
 * @param n - int numarul de elemente ale listei a
 * @return numarul de 0 de la sfarsitul produsului numerelor din lista
 */
int exponent_10_lista(int a[], int n) {
    int exp2 = 0, exp5 = 0, exp10 = 0, aux;

    for( int i = 1; i <= n; i ++) {
        aux = a[i];
        if (aux % 2 == 0 || aux % 5 == 0) {
            while (aux % 2 == 0) {
                aux /= 2;
                exp2++;
            }
            while (aux % 5 == 0) {
                aux /= 5;
                exp5++;
            }
        }
    }
    if( exp2 < exp5) return exp2;
    else return exp5;
}