//
// Created by Mihai Moldovan on 19.06.2024.
//

#ifndef PROJECT_EXCEPTION_H
#define PROJECT_EXCEPTION_H
#include <exception>
#include <string>
using std::exception;
using std::string;

class Exception: public exception {
public:
    Exception(string msg): msg{msg}{};

    string what() {
        return msg;
    }
private:
    string msg;
};


#endif //PROJECT_EXCEPTION_H
