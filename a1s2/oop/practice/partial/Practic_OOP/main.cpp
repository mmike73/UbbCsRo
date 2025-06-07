#include <QtWidgets/QApplication>
#include "service.h"
#include "repo.h"
#include "gui.h"
#include "test.h"
#include "validation.h"

int start(int argc, char** argv) {
    QApplication a(argc, argv);
    Repo repo("/Users/mihaimoldovan/Desktop/Practic_OOP/logs");
    Validation v;
    Service service(repo,v);
    GUI gui(service);
    gui.show();
    a.exec();
}


int main(int argc, char *argv[]) {
    Test t;
    t.run_all();
    start(argc, argv);
}
