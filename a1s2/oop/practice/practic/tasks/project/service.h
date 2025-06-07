//
// Created by Mihai Moldovan on 19.06.2024.
//

#ifndef PROJECT_SERVICE_H
#define PROJECT_SERVICE_H
#include "repo.h"
#include "validation.h"
#include "Observer.h"

class Service: public Subject {
public:
    //constructor
    Service(Repo& r, Validation& v);

    //adauga un task
    void adauga_task(Task& t);

    //cauta task dupa id - intreg
    Task cauta_dupa_id(int id) const;

    void modifica_stare_dupa_id(int id, string stare);

    //cauta task dupa programator - string
    Task cauta_dupa_programator(string programator) const;

    //returneaza toate taskurile
    vector<Task> get_all_tasks() const;

private:
    Repo& repo;
    Validation& valid;
};


#endif //PROJECT_SERVICE_H
