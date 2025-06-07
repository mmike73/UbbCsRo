#include <iostream>

int vizitat[11],n;
int m_a[11][11];

void dfs(int start) {
    int i;
    vizitat[start] = 1;
    for( int i = 1; i <= n; ++i)
        if( m_a[start][i] == 1 && vizitat[i] == 0)
            dfs(i);
}

int conex() {
    dfs(1);
    for( int i = 1; i <= n; ++i)
        if( vizitat[i] == 0) return 0;
    return 1;
}


/**
 * @brief functi numara numarul de apelur ale dfs necesare pentru a parcurge fiecare nod, acest numar corespunzand numarului de componente conexe
 * daca functia returneaza 1, atunci graful este garantat conex
 * @param matrice_adiacenta 
 * @param nr_noduri 
 * @return int numarul de componente conexe ale grafului transmis
 */
int determina_numar_componentte_conexe( int nr_noduri) {
    int cnt_componente_conexe = 0, k = 1, vizitate[nr_noduri + 1], comp_conexa[nr_noduri + 1];
    for( int i = 1; i <= nr_noduri; ++i) vizitate[i] = 0;
    while( k <= nr_noduri) {
        for( int i = 1; i <= nr_noduri; ++i) 
            comp_conexa[i] = 0;

        dfs(k);

        for( int i = 1; i <= nr_noduri; ++i) 
            if( comp_conexa[i] == 1)
                vizitate[i] = 1;

        while( vizitate[k] == 1) k++;
        cnt_componente_conexe++;
    }
    return cnt_componente_conexe;
}