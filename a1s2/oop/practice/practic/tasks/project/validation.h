//
// Created by Mihai Moldovan on 19.06.2024.
//

#ifndef PROJECT_VALIDATION_H
#define PROJECT_VALIDATION_H
#include "exception.h"
#include "domain.h"

class Validation {
private:
    void valid_id(const Task& t);
    void valid_descriere(const Task& t);
    void valid_programatori(const Task& t);
    void valid_stare(const Task& t);
public:
    void valid_task(const Task& t);
};


#endif //PROJECT_VALIDATION_H
