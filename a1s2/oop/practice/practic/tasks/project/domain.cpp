//
// Created by Mihai Moldovan on 19.06.2024.
//

#include "domain.h"


Task::Task(int id, string descriere, vector<string> programatori, string stare):
    id{id}, descriere{descriere}, programatori{programatori}, stare{stare} {}

int Task::get_id() const {
    return id;
}

string Task::get_descriere() const {
    return descriere;
}

vector<string> Task::get_programatori() const {
    return programatori;
}

string Task::get_stare() const {
    return stare;
}

void Task::set_stare(string stare_noua) {
    stare = stare_noua;
}

string Task::get_string() const {
    string progr;
    for(auto& programator: programatori) progr += programator + ',';
    return std::to_string(id) + ',' + descriere + ',' + progr + stare + '\n';
}
