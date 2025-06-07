//
// Created by Mihai Moldovan on 28.02.2024.
//
#include <stdio.h>
/**
 * funcția găsște interpretările numărului ca suma de numere naturale consecutive
 *
 * parametri de iesire:
 * @param a lista vida de numere intregi - furnizeaza inceputul intervalului
 * @param b lista vida de numere intregi - furnizeaza sfarsitul intervalului
 *
 * parametru de intrare;
 * @param s int pozitiv, numarul pentru care se afla fiecare reprezentare ca suma de numere consecutive
 * @return numarul de reprezentari
 */
int reprezentari_s(int a[], int b[], int s) {
    int cnt = 0, sum = 0;
    for( int i = 1; i < s / 2; i ++) {
        sum = i;
        if( sum + i + 1 <= s)
            for( int j = i + 1; j <= s / 2; j ++) {
                if (sum != s && sum + j <= s) {
                    sum += j;
                    if (sum == s) {
                        cnt++;
                        a[cnt] = i;
                        b[cnt] = j;
                    }
                }
                else
                    break;
            }

    }
    return cnt;
}