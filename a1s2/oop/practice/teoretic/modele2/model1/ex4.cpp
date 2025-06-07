//
// Created by Mihai Moldovan on 20.06.2024.
//
#include "carnet.h"
#include <iostream>

int main() {
    Carnet<int> cat;
    cat.add("SDA", 9);
    cat.add("OOP", 7);
    cat.add("FP", 10);

    std::cout << cat["OOP"] << '\n';
    cat.removeLast().removeLast();

    try {
        std::cout << cat["OOP"];
    } catch(exception& e) {
        std::cout << "Nu exista note pentru OOP\n";
    }

    try {
        std::cout << cat["FP"];
    } catch(exception& e) {
        std::cout << "Nu exista note pentru FP\n";
    }

}