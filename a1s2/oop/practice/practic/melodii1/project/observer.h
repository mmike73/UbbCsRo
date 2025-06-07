//
// Created by Mihai Moldovan on 18.06.2024.
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
public:
    void addObserver(Observer* obs) {
        observers.push_back(obs);
    }

    void removeObserver(Observer* obs) {
        observers.erase(remove(observers.begin(),observers.end(),obs));
    }

    void notify() {
        for(Observer* obs: observers) {
            obs->update();
        }
    }

private:
    vector<Observer*> observers;
};


#endif //PROJECT_OBSERVER_H
