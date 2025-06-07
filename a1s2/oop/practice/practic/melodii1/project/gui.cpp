//
// Created by Mihai Moldovan on 18.06.2024.
//

#include "gui.h"

void GUI::init_window() {
    setLayout(main_ly);
    main_ly->addLayout(main_ly_1);

    model = new MyModel{service};
    table->setModel(model);
    main_ly_1->addWidget(table);

    QFormLayout* mod_form = new QFormLayout;
    mod_form->addRow("Titlu:",edit_title);
    mod_form->addRow("Rank:",slider_rank);
    slider_rank->setRange(0,10);
    mod_form->addWidget(modifica);
    mod_form->addWidget(sterge);
    mod_form->addWidget(exit);

    gv->setFixedSize(1200,500);
    gs->setSceneRect(0,0,900,190);
    gv->setScene(gs);
    main_ly->addWidget(gv);
    main_ly_1->addLayout(mod_form);

    load_data();
}

void GUI::load_data() {
    update();

    gs->clear();
    int spacing = gs->width() / (model->ranks.size() + 2);
    int start = spacing;
    std::cout << "Map:\n";
    for(auto& i:model->ranks) {
        std::cout << i.first << " " << i.second << '\n';
        QGraphicsRectItem* r = new QGraphicsRectItem;
        r->setRect(0,0,30,i.second * 30);
        r->setPos(start,20 - i.second * 30);
        r->setBrush(Qt::red);
        gs->addItem(r);
        start += spacing;
    }
}

void GUI::make_connections() {

    QObject::connect(table->selectionModel(),&QItemSelectionModel::selectionChanged,[&]() {
        if(table->selectionModel()->selectedIndexes().isEmpty()) {
            return;
        }
        int row = table->selectionModel()->selectedIndexes()[0].row();
        int column = table->selectionModel()->selectedIndexes()[0].column();

        int id_selectat = std::stoi(model->data(model->index(row,0)).toString().toStdString());
        Melodie m = service.cauta_melodie(id_selectat);

        edit_title->setText(QString::fromStdString(m.get_titlu()));
        string id = std::to_string(m.get_id());
        id_sel->setText(QString::fromStdString(id));
        slider_rank->setValue(m.get_rank());
    });
    QObject::connect(modifica,&QPushButton::clicked,[&]() {
        int rank_nou = slider_rank->value();
        string titlu_nou = edit_title->text().toStdString();

        int id = std::stoi(id_sel->text().toStdString());
        Melodie m = service.cauta_melodie(id);

        m.set_rank(rank_nou);
        m.set_titlu(titlu_nou);

        service.modifica_melodie(id,m);
        load_data();
        update();
    });
    QObject::connect(exit,&QPushButton::clicked,[&]() {
        close();
    });
    QObject::connect(sterge,&QPushButton::clicked,[&]() {

        int current_id = id_sel->text().toInt();
        try {
            service.sterge_melodie(current_id);
        } catch (Exception& e) {
            QMessageBox* message = new QMessageBox;
            message->setText(QString::fromStdString(e.what()));
            message->exec();
        }
        load_data();
    });
}