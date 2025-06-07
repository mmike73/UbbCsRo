//
// Created by Mihai Moldovan on 19.06.2024.
//

#include "service.h"

Service::Service(Repo& r, Validation& v): repo{r}, valid{v} {}

void Service::adauga_task(Task& t) {
    try {
        valid.valid_task(t);
    } catch(Exception(&e)) {
        throw Exception(e.what());
    }
    repo.add(t);
    notify();
}

Task Service::cauta_dupa_id(int id) const {
    vector<Task> all = repo.get_all();
    for(auto& task: all) {
        if(task.get_id() == id) return task;
    }
    std::cout << "Throw Excception\n";
}

void Service::modifica_stare_dupa_id(int id, string stare) {
    repo.modifica_stare_dupa_id(id, stare);
}


Task Service::cauta_dupa_programator(string programator) const {
    vector<Task> all = repo.get_all();
    for(auto& task: all) {
        vector<string> all_programmers = task.get_programatori();
        auto it = all_programmers.begin();
        while(it != all_programmers.end()) {
            if(it->data() == programator) return task;
            it++;
        }
    }
    std::cout << "Throw Excception\n";
}



vector<Task> Service::get_all_tasks() const {
    return repo.get_all();
}