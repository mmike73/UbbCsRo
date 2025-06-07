//
// Created by Mihai Moldovan on 18.05.2024.
//

#ifndef P1_EXCEPTION_H
#define P1_EXCEPTION_H
#include <exception>
#include <string>

class Exception: public std::exception {
public:
    Exception(const std::string msg): msg{msg} {}

    const char* what() const noexcept override {
        return msg.c_str();
    }

private:
    std::string msg;
};


#endif //P1_EXCEPTION_H
