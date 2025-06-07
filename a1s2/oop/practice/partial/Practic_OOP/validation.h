//
// Created by Mihai Moldovan on 22.05.2024.
//

#ifndef PRACTIC_OOP_VALIDATION_H
#define PRACTIC_OOP_VALIDATION_H
#include "domain.h"

class Validation {
public:
    void valid(Log& l);
private:
    bool valid_id(Log& l);
    bool valid_pid(Log& l);
    bool valid_level(Log& l);
};


#endif //PRACTIC_OOP_VALIDATION_H
