#include <QApplication>
#include "gui.h"
#include "repo_procesoare.h"
#include "repo_placi.h"
#include "validator.h"
#include "tests.h"

int start(int argc, char *argv[]) {
    QApplication a(argc, argv);
    FileRepoProcesoare repo_procesoare{"/Volumes/D/Faculta/A1S2/OOP/practice/partial/p1/test_procesoare"};
    FileRepoPlaci repo_placi{"/Volumes/D/Faculta/A1S2/OOP/practice/partial/p1/test_placi"};
    Validator v;
    Service service{repo_placi,repo_procesoare, v};
    GUI gui{service};
    gui.show();
    return a.exec();
}

int main(int argc, char *argv[]) {
    Tests t;
    t.run_all();
    start(argc,argv);
    return 0;
}
