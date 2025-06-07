#include "test.h"
#include <QApplication>
#include "gui.h"
#include "validation.h"

int start(int argc, char *argv[]) {
    QApplication a(argc,argv);
    Repo r{"/Volumes/D/Faculta/A1S2/OOP/practice/practic/tasks/project/test_file"};
    Validation v;
    Service s{r,v};
    GUI gui{s};

    gui.show();
    a.exec();
}

int main(int argc, char *argv[]) {
    Test t;
    t.test_all();

    start(argc, argv);
}
