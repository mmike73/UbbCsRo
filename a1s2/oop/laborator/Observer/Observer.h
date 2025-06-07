#pragma once
#include <vector>
class Observer {
public:
	virtual void update()=0;
};

class Subject {
private:
	std::vector<Observer*> observers;
public:
	void addObserver(Observer* obs) {
		this->observers.push_back(obs);

	}
	void removeObserver(Observer* obs) {
		this->observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
	
	}
	void notify() {
		for (Observer* obs : observers) {
			obs->update();
		}
	}
};