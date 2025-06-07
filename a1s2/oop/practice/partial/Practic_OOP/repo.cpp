//
// Created by Mihai Moldovan on 22.05.2024.
//
#include "repo.h"

void Repo::read_from_file() {
    std::ifstream fin(cale_fisier);

    string id, content, PID_str, level;
    int PID;

    string line;
    while(getline(fin,line)) {
        stringstream fields(line);

        getline(fields,id,',');
        getline(fields,content,',');
        getline(fields,PID_str,',');
        getline(fields,level,',');

        PID = stoi(PID_str);

        Log l(id,content,PID,level);
        //v.valid(l);
        //daca mai am timp

        repo.push_back(l);
    }
}

void Repo::add_item(Log& l) {
    if(search_item(l.get_id()).get_id() == "invalid") {
        repo.push_back(l);
    }
    std::cout << repo.size() << '\n';
    for(auto& i:repo) {
        std::cout << i.get_id() << '\n';
    }
}

Log Repo::search_item(string id) {
    for(auto& item:repo) {
        if( item.get_id() == id) return item;
    }
    Log l("invalid","",-1,"");
    return l;
}

vector<Log> Repo::get_all() {
    return repo;
}
