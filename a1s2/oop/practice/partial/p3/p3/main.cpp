#include <QtWidgets/QApplication>
#include "gui.h"
#include "test.h"

int start(int argc, char** argv) {
    QApplication a(argc,argv);
    FileRepo repo("/Volumes/D/Faculta/A1S2/OOP/practice/partial/p3/p3/elevi");
    Service service(repo);
    GUI gui(service);
    gui.show();
    a.exec();
}

int main(int argc, char *argv[]) {
    Test t;
    t.run_all();
    start(argc,argv);
    return 0;
}
