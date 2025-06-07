//
// Created by Mihai Moldovan on 19.06.2024.
//

#include "test.h"
#include <assert.h>

void Test::test_all() {
    test_domain();
    test_service();
    test_repo();
    test_valid();
}
void Test::test_domain() {
    Task t{1,"da",{"a","b","c"},"ad"};
    assert(t.get_id() == 1);
    assert(t.get_descriere() == "da");
    assert(t.get_programatori()[0] == "a");
    assert(t.get_programatori()[1] == "b");
    assert(t.get_programatori()[2] == "c");
    assert(t.get_stare() == "ad");
    t.set_stare("Danger");
    assert(t.get_stare() == "Danger");
}

void Test::test_repo() {
    Repo r{"/Volumes/D/Faculta/A1S2/OOP/practice/practic/tasks/project/test_file"};
    assert(r.get_all().size() == 3);
    assert(r.seaarch(1).get_descriere() == "a");
}
void Test::test_service() {
    Repo r{"/Volumes/D/Faculta/A1S2/OOP/practice/practic/tasks/project/test_file"};
    Validation v;
    Service s{r, v};
    assert(s.get_all_tasks().size() == 3);
    assert(s.cauta_dupa_programator("pd").get_id() == 2);
    assert(s.cauta_dupa_id(3).get_stare() == "closed");
}
void Test::test_valid() {

}
