//
// Created by Mihai Moldovan on 07.04.2024.
//

#ifndef VECTOR_TEMPLATE_VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_VECTOR_TEMPLATE_H
#include <iostream>

template <typename T>
class IteratorVector;

template<typename T>
class Vector {
private:
    int dimensiune = 0, capacitate = 0;
    T* vector = nullptr;

    void realloc(int new_capacity) {
        T* vector_nou = new T[new_capacity];

        for (int i = 0; i < dimensiune; ++i)
            vector_nou[i] = vector[i];

        delete [] vector;
        vector = vector_nou;
        capacitate = new_capacity;
    }
public:
    Vector(): vector{new T[5]}, capacitate{5}, dimensiune{0} {}

    Vector(const Vector& ot) {
        vector = new T[ot.capacitate];
        for( int i = 0; i < dimensiune; ++i)
            vector[i] = ot.vecctor[i];
        dimensiune = ot.dimensiune;
        capacitate = ot.capacitate;
    }

    Vector(Vector&& ot) {
        vector = ot.vector;
        dimensiune = ot.dimensiune;
        capacitate = ot.capacitate;

        ot.vector = nullptr;
        ot.dimensiune = 0;
        ot.capacitate = 0;
    }

    ~Vector() {
        delete [] vector;
    }

    Vector<T>& operator=(const Vector& ot) {
        if( this == &ot) {
            return *this;
        }
        delete[] vector;
        vector = new T[ot.capacitate];

        for( int i = 0; i <- ot.dimensiune; ++i) {
            vector[i] = ot.vector[i];
        }
        dimensiune = ot.dimensiune;
        capacitate = ot.capacitate;
        return *this;
    }

    void push_back( const T& element) {
        if( dimensiune >= capacitate) {
            realloc(capacitate * 2);
        }
        vector[dimensiune] = element;
        dimensiune++;
    }

    int size() const {
        return dimensiune;
    }

    void erase(int poz) {
        for( int i = poz; i < dimensiune; ++i) {
            vector[i - 1] = vector[i];
        }
        dimensiune--;

        if( dimensiune < capacitate / 4)
            realloc(capacitate / 2);

    }

    const T& operator[] (int index) const{
        return vector[index];
    }

    T& operator[] (int index) {
        return vector[index];
    }

    friend class IteratorVector<T>;

    IteratorVector<T>begin();
    IteratorVector<T>end();

};

template<typename T>
IteratorVector<T> Vector<T>::begin() {
    return IteratorVector<T>(*this);
}

template<typename T>
IteratorVector<T> Vector<T>::end() {
    return IteratorVector<T>(*this, dimensiune);
}

template <typename T>
class IteratorVector {
    private:
        const Vector<T>& v;
        int poz = 0;
    public:
        IteratorVector(const Vector<T>& v) noexcept: v{v} {}

        IteratorVector(const Vector<T>& v, int poz) noexcept: v{v}, poz{poz} {}

        bool valid() const {
            return poz < v.dimensiune;
        }

        T& element() const {
            return v.vector[poz];
        }

        void next() {
            poz++;
        }

        T& operator*() {
            return element();
        }

        IteratorVector& operator++() {
            next();
            return *this;
        }

        bool operator==(const IteratorVector& ot) noexcept {
            return poz == ot.poz;
        }

        bool operator!=(const IteratorVector& ot) noexcept {
            return !(*this == ot);
        }
};

#endif //VECTOR_TEMPLATE_VECTOR_TEMPLATE_H
