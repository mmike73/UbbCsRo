#include <fstream>
#include <iostream>
#include <vector>

#include "../nod.h"
#include "../muchie.h"

#define INF 100000

class Graf {
public:
    
    int n, m;

    int** matrice_adiacenta;
    int** lista_incidenta;
    //...

    Nod* noduri;
    Muchie* muchii;

    int** matricea_drumurilor;

    std::vector<Nod&> S;


    Graf() {
        int a, b, p;
        std::ifstream fin("graf.txt");

        fin >> n >> m;

        matrice_adiacenta = new int*[n];
        for( int i = 0; i <= n; ++i)
            matrice_adiacenta[i] = new int[n];

        noduri = new Nod[n];
        muchii = new Muchie[m];

        int i = 0;
        while(fin >> a >> b >> p) {
            matrice_adiacenta[a][b] = p;
            muchii[++i].a = a;
            muchii[i].b = b;
            muchii[i].pond = p;

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

    void sorteaza_noduri(int st, int dr) {
        for( int i = st; i < dr; ++i)
            for( int j = st + 1; j <= dr; ++j)
                if( noduri[i].d > noduri[j].d)
                    std::swap(noduri[i], noduri[j]);
    }

    Nod& cauta_nod(int indice) {
        for( int i = 1; i <= n; ++i)
            if( noduri[i].indice == indice)
                return noduri[i];
    }

    void dijkstra() {
        initializare_noduri(1);
        Nod u;
        int st = 1, dr = n;
        while(st <= dr) {
            sorteaza_noduri(st, dr);
            Nod& u = noduri[st];
            S.push_back(u);
            for( int i = 1; i <= n; ++i) {
                Nod& v = cauta_nod(i);
                if( i != u.indice && u.d != INF && u.d + matrice_adiacenta[u.indice][i] < v.d) {
                    v.d = u.d + matrice_adiacenta[u.indice][i];
                }
            }
        }
    }
};


int main() {
    Graf g;
    g.print_matrice_adiacenta();
    return 0;
}
