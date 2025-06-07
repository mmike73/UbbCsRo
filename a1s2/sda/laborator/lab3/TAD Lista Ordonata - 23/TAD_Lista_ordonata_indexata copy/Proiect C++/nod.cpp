//
// Created by Mihai Moldovan on 16.04.2024.
//
#include "nod.h"


//Nod::Nod(): e{0}, pred{nullptr}, succ{nullptr} {}
//Theta(1)
Nod::Nod(TElement e, PNod pred, PNod succ): e{e}, pred{pred}, succ{succ} {}

//Theta(1)
TElement Nod::element() {
    return e;
}

//Theta(1)
PNod Nod::predecesor() {
    return pred;
}

//Theta(1)
PNod Nod::succesor() {
    return succ;
}