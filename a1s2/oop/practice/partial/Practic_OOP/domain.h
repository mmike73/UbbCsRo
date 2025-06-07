//
// Created by Mihai Moldovan on 22.05.2024.
//

#ifndef PRACTIC_OOP_DOMAIN_H
#define PRACTIC_OOP_DOMAIN_H
#include <string>
#include <vector>
using std::vector;
using std::string;

class Log {
public:
    Log(string id, string content, int PID, string level): id{id}, content{content}, PID{PID}, level{level} {}

    string get_id() const;
    string get_content() const;
    int get_PID() const;
    string get_level() const;

    void set_content(string content_nou);
    void set_PID(int PID_nou);
    void set_level(string level_nou);

private:
    string id, content, level;
    int PID;
};


#endif //PRACTIC_OOP_DOMAIN_H
