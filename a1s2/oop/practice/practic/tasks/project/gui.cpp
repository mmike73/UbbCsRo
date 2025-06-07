//
// Created by Mihai Moldovan on 19.06.2024.
//

#include "gui.h"

GUI::GUI(Service& service): service{service} {
    init_windows();
    make_connections();
    service.addObserver(this);
}

void GUI::init_windows() {
    setLayout(main_ly);

    model = new MyModel{service};
    table->setModel(model);
    left_ly->addWidget(table);
    main_ly->addLayout(left_ly);

    QFormLayout* form = new QFormLayout;
    form->addRow("ID:",id);
    form->addRow("Descriere:",desc);
    form->addRow("Programatori (separati prin virgula):",progr);
    form->addRow("Stare (open/inprogress/closed):",stare);
    form->addRow(add);
    form->addRow(filter);
    form->addRow(exit);
    main_ly->addLayout(form);
}
void GUI::load_data() {
    model->changeMade();
}
void GUI::make_connections() {
    QObject::connect(add,&QPushButton::clicked,[&]() {
        int id_task = id->text().toInt();
        if(id_task != 0) {
            string descriere_task = desc->text().toStdString();
            string programatori_task = progr->text().toStdString();
            string status_task = stare->text().toStdString();

            vector<string> programatori_vect;
            stringstream lin(programatori_task);

            string prmer;
            while(getline(lin,prmer,',')) {
                programatori_vect.push_back(prmer);
            }
            Task t{id_task,descriere_task,programatori_vect, status_task};
            try {
                service.adauga_task(t);
            } catch (Exception& e) {
                std::cout << e.what() << '\n';
            }
        } else {
            std::cout << "ID no good\n";
        }
    });
    QObject::connect(filter,&QPushButton::clicked,[&]() {

    });
    QObject::connect(search,&QPushButton::clicked,[&]() {

    });
    QObject::connect(exit,&QPushButton::clicked,[&]() {
        close();
    });
}
