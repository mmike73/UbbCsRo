//
// Created by Mihai Moldovan on 18.04.2024.
//

#ifndef TEST_GRAFURI_GRAF_H
#define TEST_GRAFURI_GRAF_H




#define INF 100000

#include <fstream>
#include <iostream>

#include "nod.h"
#include "muchie.h"

class Graf {
public:

    int n, m, start;

    int** matrice_adiacenta;
    int** lista_incidenta;
    //...



    Nod* noduri;
    Muchie* muchii;


    Graf();

    ~Graf();

    void initializare_noduri(int start);
    void print_matrice_adiacenta();
    bool bellman_ford();
    void print_distante();
    void reconstruieste_drumuri();


};

#endif //TEST_GRAFURI_GRAF_H
