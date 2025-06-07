#include "gui.h"
#include "repo.h"
#include "service.h"
#include "teste.h"

int start(int argc, char *argv[]) {
    QApplication a(argc,argv);
    Repo repo_apartamente("/Volumes/D/Faculta/A1S2/OOP/practice/partial/untitled/apartamente");
    Service service_apartamente(repo_apartamente);
    GUI gui(service_apartamente);
    gui.show();
    a.exec();
}

int main(int argc, char *argv[]) {
    Teste t;
    t.run_all();
    start(argc,argv);

    return 0;
}
