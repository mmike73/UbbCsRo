//
// Created by Mihai Moldovan on 21.06.2024.
//

#include "ex4.h"
#include <iostream>

void adder() {
    Adder<int> add{1};
    std::cout << add.suma() << '\n';
    add = add + 7 + 3;
    add + 8;
    std::cout << add.suma() << '\n';
    add--;
    std::cout << add.suma() << '\n';
    --add--;
    std::cout << add.suma() << '\n';
}

int main() {
    adder();
    return 0;
}
