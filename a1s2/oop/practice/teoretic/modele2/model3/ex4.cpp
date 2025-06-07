//
// Created by Mihai Moldovan on 21.06.2024.
//
#include "ex4.h"

void operatii() {
    Expresie<int> exp{3};

    exp = exp + 7 + 3;
    exp = exp - 8;

    std::cout << exp.valoare();

    exp.undo();

    std::cout << exp.valoare() << "\n";

    exp.undo().undo();

    std::cout << exp.valoare() << '\n';
}