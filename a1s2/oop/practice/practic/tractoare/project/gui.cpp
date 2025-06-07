//
// Created by Mihai Moldovan on 14.06.2024.
//

#include "gui.h"


void GUI::init_window() {
    setLayout(main_layout);
    main_layout->addLayout(left_right_ly);

    //!IMPORTANT
    model = new MyTableModel(service);
    table->setModel(model);

    //tipuri_tr->setModel(model);

    left_ly->addWidget(table);

    mid_ly->addWidget(tipuri_tr);

    auto form_ly = new QFormLayout;
    form_ly->addRow("ID",id);
    form_ly->addRow("Denumire",denumire);
    form_ly->addRow("Tip",tip);
    form_ly->addRow("Numar roti",nr_roti);

    right_ly->addLayout(form_ly);
    right_ly->addWidget(adaugare);
    right_ly->addWidget(exit);

    left_right_ly->addLayout(left_ly);
    left_right_ly->addLayout(mid_ly);
    left_right_ly->addLayout(right_ly);

    gview->setFixedSize(1000,500);
    gscene->setSceneRect(0,0,1000,500);
    gview->setScene(gscene);
    main_layout->addWidget(gview);

    //QGraphicsEllipseItem* ball = new QGraphicsEllipseItem{ 0,0,100,100 };
    //ball->setPos(gscene->width() / 2, gscene->height()/2 );
    //ball->setBrush(Qt::red);
    //gscene->addItem(ball);

}

void GUI::make_connections() {
    QObject::connect(exit,&QPushButton::clicked,[&]() {
        close();
    });
    QObject::connect(adaugare,&QPushButton::clicked,[&]() {
        string id_t_string = id->text().toStdString();
        string denumire_t = denumire->text().toStdString();
        string tip_t = tip->text().toStdString();
        string nr_roti_t_string = nr_roti->text().toStdString();

        string errors;
        int id_t, nr_roti_t;
        try {
            id_t = std::stoi(id_t_string);
        } catch(std::exception& e) {
            errors += "ID trebuie sa fie intreg pozitiv!";
        }
        try {
            nr_roti_t = std::stoi(nr_roti_t_string);
        } catch(std::exception& e) {
            errors += "\n\n";
            errors += "Nr roti trebuie sa fie intreg pozitiv!";
        }
        if(errors.size() > 0) {
            QMessageBox *msg_err = new QMessageBox;
            msg_err->setText(QString::fromStdString(errors));
            msg_err->exec();
        } else {
            Tractor t{id_t,denumire_t,tip_t,nr_roti_t};
            try {
                service.add_tractor(t);
                load_data();
            } catch (Exception& e) {
                QMessageBox *msg_err = new QMessageBox;
                msg_err->setText(QString::fromStdString(e.what()));
                msg_err->exec();
            }
        }
    });
    QObject::connect(table->selectionModel(),&QItemSelectionModel::selectionChanged,[&]() {
        if(table->selectionModel()->selectedIndexes().isEmpty()) {
            std::cout << "Empty selection\n";
            return;
        }
        int row = table->selectionModel()->selectedIndexes()[0].row();
        int id_selectat = stoi(model->data(model->index(row,0)).toString().toStdString());
        Tractor t = service.cauta_tractor_dupa_id(id_selectat);
        gscene->clear();
        gscene->clear();
        vector<QGraphicsEllipseItem*> roti;
        for(int i = 0 ; i < t.get_nr_roti();++i) {
            QGraphicsEllipseItem* roata = new QGraphicsEllipseItem{15,10,20,20};
            roata->setBrush(Qt::red);
            roti.push_back(roata);
            roata->setFlags(QGraphicsEllipseItem::ItemIsSelectable | QGraphicsEllipseItem::ItemIsFocusable);

        }
        int dist = gscene->width()/(roti.size() + 2);
        int start = dist;
        for(auto& i:roti) {
            i->setPos(start,gscene->height() / 2);
            gscene->addItem(i);
            start += dist;
        }
    });
    QObject::connect(tipuri_tr,&QComboBox::currentIndexChanged,[&]() {
        std::cout << "Combo selection: " << tipuri_tr->currentText().toStdString() << '\n';
        model->set_tip_selectat(tipuri_tr->currentText().toStdString());
    });

}

void GUI::load_data() {
    update();
    map<QString,bool> check;
    tipuri_tr->clear();
    for(int row = 0; row < model->rowCount(); ++row) {
        QString type = model->data(model->index(row,2)).toString();
        if(check.find(type) == check.end()) {
            check.insert({type, 0});
            tipuri_tr->addItem(type);
        }
    }
    check.empty();
}