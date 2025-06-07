#include <QApplication>
#include "test.h"
#include "gui.h"

int start(int argc, char *argv[]) {
    QApplication a(argc,argv);
    Repo r{"/Volumes/D/Faculta/A1S2/OOP/practice/practic/melodii1/project/melodii"};
    Service s{r};
    GUI g{s};
    g.show();
    a.exec();
}

int main(int argc, char *argv[]) {
    Test t;
    t.test_all();
    start(argc,argv);
    return 0;
}
