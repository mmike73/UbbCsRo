#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define INF 10000

typedef struct Nod {
    int indice;
    char color;
    int d;
    struct Nod *pi;
} Nod;



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

int main() {
    int nr_noduri, start, a, b, **m_a, sfarsit;
    FILE *file_ptr = fopen("graf.txt", "r");
    FILE *file_ptr_o = fopen("graf_out.txt", "w");

    if (file_ptr == NULL) {
        printf("Eroare la deschiderea fisierului graf.txt!");
        return -1;
    }
    fscanf(file_ptr, "%d %d %d", &nr_noduri, &start, &sfarsit);

    Nod noduri[nr_noduri + 1];
    void *queue[nr_noduri + 2];
    m_a = (int **)malloc((nr_noduri + 1) * sizeof(int*));
    for (int i = 0; i <= nr_noduri; ++i) {
        noduri[i].color = 'a';
        noduri[i].d = INF;
        noduri[i].pi = NULL;
        noduri[i].indice = i;
        m_a[i] = (int *)malloc((nr_noduri + 1) * sizeof(int));
    }
    for (int i = 0; i <= nr_noduri; ++i)
        for (int j = 0; j <= nr_noduri; ++j)
            m_a[i][j] = 0;

    while (fscanf(file_ptr, "%d %d", &a, &b) != EOF) { // Corectat de la != -1 la != EOF
        m_a[a][b] = 1;
        m_a[b][a] = 1;
    }
    fclose(file_ptr);

    moore(noduri, nr_noduri, m_a, queue, &noduri[start]);

    if(noduri[sfarsit].d == INF) {
        fprintf(file_ptr_o,"Nu exista drum!!!\n");
        return 0;
    }

    Nod** drum = moore_drum(noduri, &noduri[sfarsit]);
    fprintf(file_ptr_o, "Drumul cel mai scurt de la %d la %d: ", start, nr_noduri);
    
    for (int i = 0; i <= noduri[sfarsit].d; ++i) {
        fprintf(file_ptr_o,"%d ", drum[i]->indice);
    }
    printf("\n");

    free(drum);
    for (int i = 0; i <= nr_noduri; ++i)
        free(m_a[i]);
    free(m_a);

    return 0;
}
