/**
 * @brief determina nodurile izolate - numarul de linii din matricea de adiacenta care sunt nule arata ca nodul nu e adiacent cu altul
 * 
 * @param matrice_adiacenta caracteristica grafului
 * @param n numarul de muchii
 * @param a nodurile izolate - parametru de iesire
 * @return int numarul de noduri izolate gasite
 */
int determina_noduri_izolate( int matrice_adiacenta[][101], int n, int a[]) {
    int nr_noduri_izolate = 0;
    for( int i = 1; i <= n; ++i) {
        int ok = 1;
        for( int j = 1; j <= n; ++j) 
            if( matrice_adiacenta[i][j]) ok = 0;
        if( ok) {
            nr_noduri_izolate++;
            a[nr_noduri_izolate] = i;
        }
    }
    return nr_noduri_izolate;
}

/**
 * @brief teesteaza daca graful e regular, are muchii de grad egal
 * 
 * @param matrice_adiacenta 
 * @param n 
 * @return int 1 - daca e regulara
 *             0 - faca nu e regulara
 */
int determina_regularitate( int matrice_adiacenta[][101], int n) {
    int cmp = 0;
    for( int i = 1; i <= n; ++i) {
        int suma = 0;
        for( int j = 1; j <= n; ++j) suma += matrice_adiacenta[i][j];
        if( cmp == 0) cmp = suma;
        else if(cmp != suma) return 0;
    }
    return 1;
}