//
// Created by Mihai Moldovan on 16.04.2024.
//

#ifndef LISTA_ORDONATA___CU_POZITIE_INDICE__INDEXATA__NOD_H
#define LISTA_ORDONATA___CU_POZITIE_INDICE__INDEXATA__NOD_H
#include "LO.h"

typedef int TComparabil;
typedef TComparabil TElement;
class Nod;
typedef Nod *PNod;

class Nod {
public:
    friend class LO;
    Nod();
    Nod(TElement e, PNod pred, PNod succ);
    TElement element();
    PNod predecesor();
    PNod succesor();
private:
    TElement e;
    PNod pred, succ;
};





#endif //LISTA_ORDONATA___CU_POZITIE_INDICE__INDEXATA__NOD_H
