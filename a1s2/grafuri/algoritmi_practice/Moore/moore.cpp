#include <stdlib.h>
#include "nod.h"
#define INF 10000

Nod* queue[1001];
/**
 * @brief pentru fiecare nod specifica distanta minima pana la sursa 
 *        si nodul parinte in cazul drumului de lungime minima
 */
int moore(Nod noduri[], int nr_noduri, int **m_a, Nod* queue[], Nod* start) {
    start->d = 0;
    int st = 1, end = 0;
    queue[++end] = start;
    while (st <= end) {
        Nod* crt = queue[st];
        st++;
        for (int i = 1; i <= nr_noduri; ++i)
            if (m_a[crt->indice][i] && noduri[i].d == INF) {
                noduri[i].pi = crt;
                noduri[i].d = crt->d + 1;
                queue[++end] = &noduri[i];
            }
    }
    return end;
}

/**
 * @brief recreeaza drumul de lungime minima

 */
Nod** moore_drum(Nod noduri[], Nod* dest) {
    int k = dest->d;
    Nod** drum = (Nod **)malloc(sizeof(Nod *) * (k + 1));
    drum[k] = dest;
    while (k > 0) {
        drum[k - 1] = drum[k]->pi;
        k--;
    }
    return drum;
}