//
// Created by Mihai Moldovan on 18.06.2024.
//

#ifndef PROJECT_SERVICE_H
#define PROJECT_SERVICE_H
#include "repo.h"
#include "observer.h"

class Service: public Subject {
public:
    //constructor
    Service(Repo& r);

    //sterge melodie
    void sterge_melodie(int id);

    //modifica o melodie
    void modifica_melodie(int id, Melodie& m );

    Melodie cauta_melodie(int id) const;

    //returneaza toate melodiile
    vector<Melodie> get_all_melodii() const;

    map<int,int> get_all_ranks() const;

    map<string,int> get_all_artists() const;

private:
    Repo& repo;
};


#endif //PROJECT_SERVICE_H
