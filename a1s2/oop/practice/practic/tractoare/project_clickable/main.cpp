#include <QApplication>
#include "test.h"
#include "gui.h"

int start(int argc, char*argv[]) {
    QApplication a(argc, argv);
    Repo r("tractoare");
    Valid v;
    Service s(r,v);
    GUI gui(s);

    gui.show();
    a.exec();
}

int main(int argc, char *argv[]) {
    Test t;
    t.run_all();

    start(argc,argv);
    return 0;
}
