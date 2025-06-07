//
// Created by Mihai Moldovan on 18.04.2024.
//

#ifndef TEST_NOD_H
#define TEST_NOD_H

class Nod {
public:
    int indice;
    int d, f;
    Nod* pi;
    char color;

    Nod(): indice(0), d(0), f(0), pi(nullptr), color('w') {};
};

#endif //TEST_NOD_H
