//
// Created by Mihai Moldovan on 22.06.2024.
//

#ifndef PROJECT_EXCEPTION_H
#define PROJECT_EXCEPTION_H
#include <exception>
#include <string>
using std::exception;
using std::string;

class Exception: public exception {
public:
    string msg;
public:

    Exception(string msg): msg{msg} {}

    string what() {
        return msg;
    }

};


#endif //PROJECT_EXCEPTION_H
