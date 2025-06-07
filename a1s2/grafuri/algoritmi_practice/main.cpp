#include <fstream>
#include <iostream>

#include "nod.h"
#include "muchie.h"

#define INF 100000

class Graf {
private:

    int n, m;

    int** matrice_adiacenta;
    int** lista_incidenta;
    //...

    Nod* noduri;
    Muchie* muchii;

    int** matricea_drumurilor;

public:
    Graf() {
        int a, b;
        std::ifstream fin("graf.txt");

        fin >> n >> m;

        matrice_adiacenta = new int*[n];
        for( int i = 0; i <= n; ++i)
            matrice_adiacenta[i] = new int[n];

        noduri = new Nod[n];
        muchii = new Muchie[m];

        int i = 0;
        while(fin >> a >> b) {
            matrice_adiacenta[a][b] = 1;
            matrice_adiacenta[b][a] = 1;
            muchii[++i].a = a;
            muchii[++i].b = b;
        }

        for( int i = 1; i <= n; ++i)
            noduri[i].indice = i;

        fin.close();
    }

    ~Graf() {
        for( int i = 0; i <= n; ++i)
            delete [] matrice_adiacenta[i];
        delete [] matrice_adiacenta;
        delete [] noduri;
        delete [] muchii;
    }
    //////////

    void initializare_noduri(int start) {
        for( int i = 1; i <= n; ++i)
            noduri[i].d = INF, noduri[i].pi = nullptr;
        noduri[start].d = 0;
    }

    void print_matrice_adiacenta() {
        for( int i = 1; i <= n; ++i, std::cout << '\n')
            for( int j = 1; j <= n; ++j)
                std::cout << matrice_adiacenta[i][j] << ' ';
    }

};


int main() {
    Graf g;
    std::cout << "HW!!!";
    //g.print_matrice_adiacenta();
    return 0;
}
