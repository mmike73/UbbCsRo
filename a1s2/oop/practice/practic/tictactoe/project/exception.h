//
// Created by Mihai Moldovan on 21.06.2024.
//

#ifndef PROJECT_EXCEPTION_H
#define PROJECT_EXCEPTION_H
#include <exception>
#include <string>
using std::exception;
using std::string;

class Exception: public exception {
private:
    string msg;
public:
    Exception(string msg): msg{msg} {};

    string what() {
        return msg;
    }
};


#endif //PROJECT_EXCEPTION_H
