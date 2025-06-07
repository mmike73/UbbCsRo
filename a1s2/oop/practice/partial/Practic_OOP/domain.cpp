//
// Created by Mihai Moldovan on 22.05.2024.
//

#include "domain.h"

string Log::get_id() const {
    return id;
}
string Log::get_content() const {
    return content;
}
int Log::get_PID() const {
    return PID;
}
string Log::get_level() const {
    return level;
}
void Log::set_content(string content_nou) {
    content = content_nou;
}
void Log::set_PID(int PID_nou) {
    PID = PID_nou;
}
void Log::set_level(string level_nou) {
    level = level_nou;
}