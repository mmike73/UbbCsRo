//
// Created by Mihai Moldovan on 21.06.2024.
//

#ifndef MODEL3_EX4_H
#define MODEL3_EX4_H

#include <iostream>
#include <memory>
#include <vector>

template <typename T>
class Expresie;

template <typename T>
class ActiuneUndo {
public:
    virtual void doUndo() = 0;
    virtual ~ActiuneUndo() = default;
};

template <typename T>
class PlusUndo: public ActiuneUndo<T> {
private:
    T elem;
    Expresie<T>& cl;
public:
    PlusUndo(T elem, Expresie<T>& cl): elem{elem}, cl{cl} {};
    void doUndo() override {
        cl - elem;
    }
};

template <typename T>
class MinusUndo: public ActiuneUndo<T> {
private:
    T elem;
    Expresie<T>& cl;
public:
    MinusUndo(T elem, Expresie<T>& cl): elem{elem}, cl{cl} {};
    void doUndo() override {
        cl + elem;
    }
};

template <typename T>
class Expresie {
public:
    Expresie(T init): total{init} {};

    Expresie<T>& operator+(T ot) {
        undo_list.push_back(std::make_unique<PlusUndo<T>>(ot,this));
        total += ot;
        return *this;
    }

    Expresie<T>& operator-(T ot) {
        undo_list.push_back(std::make_unique<MinusUndo<T>>(ot,this));
        total -= ot;
        return *this;
    }

    T valoare() {
        return total;
    }

    Expresie<T>& undo() {
        undo_list.back()->doUndo();
        undo_list.pop_back();
        return *this;
    }


private:
    T total;
    std::vector<std::unique_ptr<ActiuneUndo<T> >> undo_list;
};



#endif //MODEL3_EX4_H
