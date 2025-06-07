//
// Created by Mihai Moldovan on 21.06.2024.
//

#ifndef MODEL2_EX4_H
#define MODEL2_EX4_H
#include <vector>
using std::vector;

template <typename T>
class Adder {
public:
    Adder(T n);
    Adder<T> operator+(T ot);
    Adder<T>& operator--();     // Pre-decrement
    Adder<T> operator--(int);   // Post-decrement
    T suma() const;

private:
    T total;
    vector<T> history;
};

template <typename T>
Adder<T>::Adder(T n) : total{n} {
    history.push_back(n);
}

template<typename T>
Adder<T> Adder<T>::operator+(T ot) {
    Adder<T> temp = *this;
    temp.total += ot;
    temp.history.push_back(ot);
    return temp;
}

template<typename T>
Adder<T>& Adder<T>::operator--() {
    if (history.size() > 1) { // Ensure we don't remove the initial value
        total -= history.back();
        history.pop_back();
    }
    return *this;
}

template<typename T>
Adder<T> Adder<T>::operator--(int) {
    Adder<T> temp = *this;
    --(*this);
    return temp;
}

template<typename T>
T Adder<T>::suma() const {
    return total;
}

#endif //MODEL2_EX4_H
