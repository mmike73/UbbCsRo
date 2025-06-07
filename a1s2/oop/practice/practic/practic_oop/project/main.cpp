#include <QApplication>
#include "test.h"
#include "gui.h"

int start(int argc, char** argv) {
    QApplication a(argc, argv);
    Repo r{"/Users/mihaimoldovan/Desktop/practic_oop/project/utilaje"};
    Service s{r};
    GUI gui{s};
    gui.show();
    return a.exec();
}

int main(int argc, char *argv[]) {
    Test t;
    t.run_all();
    start(argc,argv);
}
