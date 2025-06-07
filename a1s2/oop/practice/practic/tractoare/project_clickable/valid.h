//
// Created by Mihai Moldovan on 14.06.2024.
//

#ifndef PROJECT_VALID_H
#define PROJECT_VALID_H
#include "domain.h"

class Valid {
private:
    void valideaza_id(Tractor& t);
    void valideaza_denumire(Tractor& t);
    void valideaza_tip(Tractor& t);
    void valideaza_nr_roti(Tractor& t);
public:
    void valideaza_tractor(Tractor& t);
};


#endif //PROJECT_VALID_H
