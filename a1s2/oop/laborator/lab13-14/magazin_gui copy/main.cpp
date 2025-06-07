#include "repo.h"
#include "validation.h"
#include "service.h"
#include "gui.h"
#include "gui_cos.h"
#include "tests.h"
#include "cos_cumparaturi.h"

int start(int argc, char* argv[]) {
    ProduseRepoFile repo{"/Volumes/D/Faculta/A1S2/OOP/labs/lab10-11/magazin_gui/stoc"};
    Validation validare;
    CosCumparaturi cos_cumparaturi{repo};
    ServiceProduse service{repo, validare, cos_cumparaturi};
    QApplication a(argc, argv);
    GUI gui(service);
    //GUI_COS gui_cos(service);
    gui.show();
    //gui_cos.show();
    //gui.run();
    return a.exec();
}

int main(int argc, char* argv[]) {
    Tests t;
    t.run_all_tests();

    start(argc,argv);
}
