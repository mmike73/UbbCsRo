//
// Created by Mihai Moldovan on 21.06.2024.
//

#ifndef PROJECT_OBSERVER_H
#define PROJECT_OBSERVER_H
#include <vector>
using std::vector;

class Observer {
public:
    virtual void update() = 0;
};

class Subject {
private:
    vector<Observer*> observers;
public:
    void addObserver(Observer* obs);
    void removeObserver(Observer* obs);
};


#endif //PROJECT_OBSERVER_H
