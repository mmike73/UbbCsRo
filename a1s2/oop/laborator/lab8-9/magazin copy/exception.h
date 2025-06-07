//
// Created by Mihai Moldovan on 10.04.2024.
//

#ifndef LAB6_7_EXCEPTION_H
#define LAB6_7_EXCEPTION_H
#include <exception>
#include <string>

class Exception: public std::exception {
public:
    Exception(const std::string& msg): message{msg} {}

    const char* what() const noexcept override {
        return message.c_str();
    }
private:
    std::string message;
};


#endif //LAB6_7_EXCEPTION_H