//
// Created by Mihai Moldovan on 18.04.2024.
//

#include "graf.h"
#include <fstream>

Graf::Graf() {
    int a, b, p;
    std::ifstream fin("../graf.txt");

    if (!fin) {
        std::cerr << "Error: Unable to open input file!" << std::endl;
        // Handle the error (e.g., exit the program or return an error code)
    }
    std::cout << "Introdu nod sursa: ";
    std::cin >> start;
    std::cout <<"\n";
    fin >> n >> m;

    matrice_adiacenta = new int*[n + 1];
    for( int i = 0; i <= n; ++i)
        matrice_adiacenta[i] = new int[n + 1];

    muchii = new Muchie[m+1];
    noduri = new Nod[n+1];

    int i = 0;
    while(fin >> a >> b >> p) {
        matrice_adiacenta[a][b] = p;
        muchii[++i].a = a;
        muchii[i].b = b;
        muchii[i].pond = p;
    }

    for( i = 1; i <= n; ++i)
        noduri[i].indice = i;


fin.close();
}


Graf::~Graf() {
    //for( int i = 0; i <= n; ++i)
    //    delete [] matrice_adiacenta[i];
    //delete [] matrice_adiacenta;
}

void Graf::initializare_noduri(int start) {
    for( int i = 1; i <= n; ++i)
        noduri[i].d = INF;
    noduri[start].d = 0;
}

void Graf::print_matrice_adiacenta() {
    std::cout << "Noduri:\n";
    for( int i = 1; i <= n; ++i)
        std::cout << noduri[i].indice << ". " << noduri[i].d << " " << noduri[i].pi << '\n';
    std::cout << "Muchii:\n";
    for( int i = 1; i <= m; ++i)
        std::cout << muchii[i].a << ". " << muchii[i].b << " " << muchii[i].pond << '\n';
    std::cout << "Matrice:\n";
    for( int i = 1; i <= n; ++i, std::cout << '\n')
        for( int j = 1; j <= n; ++j)
            std::cout << matrice_adiacenta[i][j] << ' ';
}

void Graf::print_distante() {

    std::cout << "Nod sursa: " << start<<"\n";
    for( int i = 1; i <= n; ++i)
        std::cout <<start << " -> " << noduri[i].indice << " " << noduri[i].d << " " << '\n';
    std::cout << '\n';
}

bool Graf::bellman_ford() {
    initializare_noduri(start);
    for( int j = 1; j <= n; ++j) {
        for( int i = 1; i <= m; ++i) {
            //relax
            if(noduri[muchii[i].a].d != INF && noduri[muchii[i].a].d + muchii[i].pond < noduri[muchii[i].b].d) {
                noduri[muchii[i].b].d = noduri[muchii[i].a].d + muchii[i].pond;
                noduri[muchii[i].b].pi = &noduri[muchii[i].a];
            }
        }
    }
    for( int i = 1; i <= m; ++i) {
        //relax
        if(noduri[muchii[i].a].d != INF && noduri[muchii[i].a].d + muchii[i].pond < noduri[muchii[i].b].d)
            return false;
    }
    return true;
}

void Graf::reconstruieste_drumuri() {
    std::cout << "Drumuri:\n";
    for( int i = 1; i <= m; ++i) {
        if( i == start) continue;
        int drum[noduri[i].d + 1];
        int ind = 0;
        Nod* fin = &noduri[i];
        while(fin->indice != start) {
            std::cout << fin->indice << ' ';
            fin = fin->pi;
        }
        std::cout << start << "\n";
    }
}