//
// Created by Mihai Moldovan on 06.03.2024.
//
#include <stdio.h>

/**
 * Testeaza primialitatea numatului x.
 * @param x - numar natural
 * @return 1 - x - numar prim
 *         0 - x - nu e prim
 */
int Prim(int x) {
    if (x < 2) return 0;
    if (x == 2) return 1;
    if (x % 2 == 0) return 0;
    for (int d = 3; d * d <= x; d += 2)
        if (x % d == 0) return 0;
    return 1;
}

/**
* tipareste al n-lea temen din sirul care contine:
* pentru n - numar prim: n, n - 1, ..., 3, 2, 1
* pentru n - numar neprim: n si divizorii lui n de d ori - d - divixorul curent
* n - numar natural pozitiv maxim 10000
*/
int sir_termeni(int a[], int n) {
    for (int i = 1, j = 0; j <= n; ++i) {
        if (Prim(i)) {
            for (int k = i; k >= 1 && j <= n; k--)
                a[++j] = k;
        } else {
            a[++j] = i;
            if (i == 1) continue;
            int d = 2, aux = i;
            while (aux) {
                if (aux % d == 0) {
                    for (int k = 1; k <= d && j <= n; k++)
                        a[++j] = d;
                    while (aux % d == 0)
                        aux /= d;
                }
                d++;
                if (d * d > aux) {
                    if (j <= n)
                        for (int k = aux; k >= 1 && j <= n; k--) a[++j] = aux;
                    aux = 0;
                }
            }
        }
    }
    return 0;
}


