//
// Created by Mihai Moldovan on 22.06.2024.
//

#include "observer.h"

void Subject::notify() {
    for(auto& observer: observers) {
        observer->update();
    }
}
