#include <stdio.h>
#include <stdlib.h>
#define INF 10000

typedef struct Nod {
    int indice;
    char color;
    int d;
    struct Nod *pi;
} Nod;

int bfs( Nod noduri[], int **m_a, int nr_noduri, int ind_sursa, Nod *queue[]) {
    //initializez coada, si incep prin a adauga nodul sursa in ea
    int start = 1, end = 0;
    noduri[ind_sursa].d = 0;
    noduri[ind_sursa].color = 'g';
    queue[++end] = &noduri[ind_sursa];
    //bucla se termina cand nu mai sunt noduri de explorat
    while(start <= end) {
        Nod *crt = queue[start++];
        //parcurgem toate nodurile vecine cu nodul curent si le adaugamm in coada
        for( int i = 1; i <= nr_noduri; ++i) {
            if(noduri[i].color == 'a' && m_a[i][crt->indice]) {
                noduri[i].color = 'g';
                noduri[i].d = crt->d + 1;
                noduri[i].pi = crt;
                queue[++end] = &noduri[i];
            }
            //terminat explorarea nodului curent
            crt->color = 'b';
        }
    }
    return end;
}

int main() {
    int nr_noduri, m, start, a, b, **m_a;
    FILE *file_ptr = fopen("graf.txt","r");
    FILE *file_ptr_o = fopen("graf_out.txt","w");
    fscanf(file_ptr,"%d %d %d",&nr_noduri, &m, &start);

    Nod noduri[nr_noduri + 1];
    Nod *queue[nr_noduri + 2];
    m_a = (int **)malloc((nr_noduri + 1) * sizeof(int*));
    for( int i = 0; i <= nr_noduri; ++i) {
        noduri[i].color = 'a';
        noduri[i].d = INF;
        noduri[i].pi = NULL;
        noduri[i].indice = i;
        m_a[i] = (int *)malloc((nr_noduri + 1) * sizeof(int));
    }
    for( int i = 0; i <= nr_noduri; ++i)
        for( int j = 0; j <= nr_noduri; ++j)
            m_a[i][j] = 0;


    while(fscanf(file_ptr, "%d %d", &a, &b) != -1) {
        m_a[a][b] = 1;
        m_a[b][a] = 1;
    }

    int nr_explorate = bfs(noduri,m_a, nr_noduri, start, queue);

    for( int i = 1; i <= nr_explorate; ++i) {
        fprintf(file_ptr_o, "Nod: %d, distanta: %d\n", ((Nod*)(queue[i]))->indice, ((Nod*)(queue[i]))->d);
    }

    for( int i = 0; i <= nr_noduri; ++i)
        free(m_a[i]);
    free(m_a);
      
    return 0;
}