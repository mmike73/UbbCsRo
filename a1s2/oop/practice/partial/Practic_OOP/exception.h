//
// Created by Mihai Moldovan on 22.05.2024.
//

#ifndef PRACTIC_OOP_EXCEPTION_H
#define PRACTIC_OOP_EXCEPTION_H
#include <exception>
#include <string>
using std::string;

class Exception: public std::exception {
public:
    Exception(string msg): msg{msg} {}
    string what() {
        return msg;
    }
private:
    string msg;
};


#endif //PRACTIC_OOP_EXCEPTION_H
