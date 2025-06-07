 #include <stdio.h>
#include <stdlib.h>

typedef struct Nod {
    int indice;
    char color;
    int d, f;
    struct Nod* pi;
} Nod;

void dfs( Nod* k, int nr_noduri, Nod* crt, int **adj, int* time) {
    crt->color = 'g';
    *time = *time + 1;
    crt->d = *time;
    for( int i = 1; i <= nr_noduri; ++i) 
        if(adj[crt->indice][i] && k[i].color == 'w') {
            k[i].pi = crt;
            dfs(k, nr_noduri, &k[i], adj, time);
        }

    *time = *time + 1;
    crt->color = 'b';
    crt->f = *time;
}

int comp( const void* elem1, const void* elem2) {
    Nod f = *((Nod*)elem1);
    Nod s = *((Nod*)elem2);
    if( f.d < s.d) return -1;
    if( f.d > s.d) return 1;
    return 0;
}

int main() {
    int nr_noduri, m, start, a, b, **m_a;
    FILE *file_ptr = fopen("graf.txt","r");
    FILE *file_ptr_o = fopen("graf_out.txt","w");
    fscanf(file_ptr,"%d %d",&nr_noduri, &start);

    Nod noduri[nr_noduri + 1];
    
    //initializare
    m_a = (int **)malloc((nr_noduri + 1) * sizeof(int*));
    for( int i = 0; i <= nr_noduri; ++i) {
        noduri[i].color = 'w';
        noduri[i].d = 0;
        noduri[i].f = 0;
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

    int time = 0;
    dfs(noduri, nr_noduri, &noduri[start], m_a, &time);

    qsort(noduri, sizeof(noduri)/sizeof(*noduri), sizeof(*noduri), comp);

    fprintf(file_ptr_o,"Noduri parcurse: ");
    for( int i = 1; i <= nr_noduri; ++i)
        if( noduri[i].d != 0) {
            fprintf(file_ptr_o, "%d ", noduri[i].indice);
        }
    fprintf(file_ptr_o,".");
    
    for( int i = 0; i <= nr_noduri; ++i)
        free(m_a[i]);
    free(m_a);
      
    return 0;
}