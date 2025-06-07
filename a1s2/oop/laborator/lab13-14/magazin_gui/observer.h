//
// Created by Mihai Moldovan on 22.05.2024.
//

#ifndef MAGAZIN_GUI_OBSERVER_H
#define MAGAZIN_GUI_OBSERVER_H
#include <vector>
using std::vector;

class Observer {
public:
    virtual void update() = 0;
};

class Subject {
public:
    void addObserver(Observer* obs) {
        this->observers.push_back(obs);
    }

    void removeObsever(Observer* obs) {
        this->observers.erase(remove(observers.begin(),observers.end(),obs),observers.end());
    }

    void notify() {
        for(Observer* obs: observers) {
            obs->update();
        }
    }
private:
    vector<Observer*> observers;
};




#endif //MAGAZIN_GUI_OBSERVER_H
