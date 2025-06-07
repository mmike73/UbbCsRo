/**
 * @param matrice_adiacenta - paramatru de intrare si iesire
 *  pre: matricea de adiacenta a grafului
 *  post: dupa apelul functiei, aceasta devine matricea drumurilor
 * @param n int - numarul de noduri a grafului
 */
void creeaza_matricea_distantelor( int matrice_adiacenta[][101], int n) {
    for( int i = 1; i <= n; ++i)
        for( int j = 1; j <= n; ++j)
            if(matrice_adiacenta[i][j] == 0 && i != j)
                matrice_adiacenta[i][j] = 10000;


    for( int k = 1; k <= n; ++k) 
        for( int i = 1; i <= n; ++i)
            for( int j = 1; j <= n; ++j)
                if(matrice_adiacenta[i][k] + matrice_adiacenta[k][j] < matrice_adiacenta[i][j])
                    matrice_adiacenta[i][j] = matrice_adiacenta[i][k] + matrice_adiacenta[k][j];
}

void floyd_warshall( int** m_a, int nr_noduri) {
    for( int k = 1; k <= nr_noduri; ++k)
        for( int i = 1; i <= nr_noduri; ++i)
            for( int j = 1; j <= nr_noduri; ++j)
                if( m_a[i][j] == 0)
                    m_a[i][j] = m_a[i][k] * m_a[k][j];
}