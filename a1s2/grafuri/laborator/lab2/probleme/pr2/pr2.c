#include <stdio.h>
#include <stdlib.h>

void floyd_warshall( int** m_a, int nr_noduri) {
    for( int k = 1; k <= nr_noduri; ++k)
        for( int i = 1; i <= nr_noduri; ++i)
            for( int j = 1; j <= nr_noduri; ++j)
                if( m_a[i][j] == 0)
                    m_a[i][j] = m_a[i][k] * m_a[k][j];
}

int main() {
    int nr_noduri, start, a, b, **m_a, sfarsit;
    FILE *file_ptr = fopen("graf.txt", "r");
    FILE *file_ptr_o = fopen("graf_out.txt", "w");
    if (file_ptr == NULL) {
        printf("Eroare la deschiderea fisierului graf.txt!");
        return -1;
    }
    fscanf(file_ptr, "%d", &nr_noduri);
    
    m_a = (int **)malloc((nr_noduri + 1) * sizeof(int*));
    for (int i = 0; i <= nr_noduri; ++i) {
        m_a[i] = (int *)malloc((nr_noduri + 1) * sizeof(int));
        for (int j = 0; j <= nr_noduri; ++j)
            m_a[i][j] = 0;
    }
        
    while (fscanf(file_ptr, "%d %d", &a, &b) != EOF) { // Corectat de la != -1 la != EOF
        m_a[a][b] = 1;
    }
    fclose(file_ptr);

    floyd_warshall(m_a,nr_noduri);

    for( int i = 1; i <= nr_noduri; ++i, fprintf(file_ptr_o, "\n"))
        for( int j = 1; j <= nr_noduri; ++j)
            fprintf(file_ptr_o, "%d ", m_a[i][j]);

    for (int i = 0; i <= nr_noduri; ++i)
        free(m_a[i]);
    free(m_a);

    return 0;
}