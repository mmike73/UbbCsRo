//
// Created by Mihai Moldovan on 20.06.2024.
//

#ifndef MODEL1_CARNET_H
#define MODEL1_CARNET_H
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <exception>
using std::map;
using std::string;
using std::exception;
using std::vector;

template<typename T>
class Carnet {
public:
    Carnet();
    void add(string materie, T nota);
    Carnet<T>& removeLast();
    T operator[](string materie);

private:
    map<string,T> note;
    vector<string> order;
};

template<typename T>
Carnet<T>::Carnet() {
    note.clear();
}

template<typename T>
void Carnet<T>::add(string materie, T nota) {
    note.insert({materie,nota});
    order.push_back(materie);
}

template<typename T>
Carnet<T>& Carnet<T>::removeLast() {
    if(!order.empty()) {
        note.erase(note.find(order.back()));
        order.pop_back();
        for (auto it = note.begin(); it != note.end(); ++it) {
            std::cout << it->first << " " << it->second << '\n';
        }
    }
    return *this;
}

template<typename T>
T Carnet<T>::operator[](string materie) {
    if(note.find(materie) != note.end()) {
        return note.find(materie)->second;
    } else {
        throw exception();
    }
}



#endif //MODEL1_CARNET_H
