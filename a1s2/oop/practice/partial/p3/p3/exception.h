//
// Created by Mihai Moldovan on 22.05.2024.
//

#ifndef P3_EXCEPTION_H
#define P3_EXCEPTION_H
#include <exception>
#include <string>
using std::string;

class Exception: public std::exception{
public:
    Exception(string msg): msg{msg} {}
    string what() {
        return msg;
    }
private:
    string msg;
};


#endif //P3_EXCEPTION_H
