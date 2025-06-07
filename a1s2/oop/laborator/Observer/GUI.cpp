#include "GUI.h"

void SongManagerGUI::initializeGUIComponents()
{
	mainLayout = new QHBoxLayout;
	setLayout(mainLayout);

	leftWidget = new QWidget;
	rightWidget = new QWidget;

	leftSideLayout = new QVBoxLayout;
	leftWidget->setLayout(leftSideLayout);

	rightSideLayout = new QVBoxLayout;
	rightWidget->setLayout(rightSideLayout);

	addWidget = new QWidget;
	addWidgetLayout = new QFormLayout;
	addWidget->setLayout(addWidgetLayout);

	lblTitlu = new QLabel("Titlu:");
	editTitlu = new QLineEdit;

	lblArtist = new QLabel("Artist:");
	editArtist = new QLineEdit;

	lblGen = new QLabel("Gen:");
	editGen = new QLineEdit;

	lblDurata = new QLabel("Durata:");
	editDurata = new QLineEdit;

	addWidgetLayout->addRow(lblTitlu, editTitlu);
	addWidgetLayout->addRow(lblArtist, editArtist);
	addWidgetLayout->addRow(lblGen, editGen);
	addWidgetLayout->addRow(lblDurata, editDurata);

	addBtn = new QPushButton{ "Adauga melodie" };

	addWidgetLayout->addWidget(addBtn);

	leftSideLayout->addWidget(addWidget);

	sortGroupBox = new QGroupBox{ "Sortare" };
	sortLayout = new QVBoxLayout;
	sortGroupBox->setLayout(sortLayout);
	sortDurataRadio = new  QRadioButton{ "Sortare dupa durata" };
	sortArtistTitluRadio = new QRadioButton{ "Sortare dupa artist si titlu" };
	sortBtn = new QPushButton("Sorteaza");

	sortLayout->addWidget(sortDurataRadio);
	sortLayout->addWidget(sortArtistTitluRadio);
	sortLayout->addWidget(sortBtn);

	leftSideLayout->addWidget(sortGroupBox);

	filterWidget = new QWidget;
	filterLayout = new QFormLayout;
	filterWidget->setLayout(filterLayout);
	filterOptionsCombo = new QComboBox;
	filterOptionsCombo->addItem("Gen");
	filterOptionsCombo->addItem("Durata");
	lblFiltru = new QLabel{ "Filtru:" };
	editFiltru = new QLineEdit;
	filterBtn = new QPushButton{ "Filtrare" };

	filterLayout->addRow(lblFiltru, editFiltru);
	filterLayout->addRow(filterOptionsCombo, filterBtn);

	leftSideLayout->addWidget(filterWidget);

	reloadInitialDataBtn = new QPushButton("Afisare lista initiala");
	leftSideLayout->addWidget(reloadInitialDataBtn);

	openPlaylistBtn = new QPushButton{ "Deschide Playlist" };
	leftSideLayout->addWidget(openPlaylistBtn);
	openPlaylistLabelBtn = new QPushButton{ "Deschide Playlist Label window" };
	leftSideLayout->addWidget(openPlaylistLabelBtn);
	openPlaylistDrawBtn = new QPushButton{ "Deschide Playlist Draw"};
	leftSideLayout->addWidget(openPlaylistDrawBtn);
	


	table = new QTableWidget{ 10, 4 };
	QStringList tableHeader = { "Artist", "Titlu", "Gen", "Durata" };
	table->setHorizontalHeaderLabels(tableHeader);
    
	rightSideLayout->addWidget(table);
	mainLayout->addWidget(leftWidget);
	mainLayout->addWidget(rightWidget);
}

void SongManagerGUI::connectSignalsSlots()
{
	QObject::connect(addBtn, &QPushButton::clicked, this, [&]() {
		QString titlu = editTitlu->text();
		qDebug() << titlu;

		QString artist = editArtist->text();
		qDebug() << artist;

		QString gen = editGen->text();
		qDebug() << gen;

		QString durata = editDurata->text();
		qDebug() << durata;
		srv.addSong(titlu.toStdString(), artist.toStdString(), gen.toStdString(), stod(durata.toStdString()));
		reloadData(srv.getAllSongs());
		});

	QObject::connect(table, &QTableWidget::itemClicked, this, [this](QTableWidgetItem* item) {
		qDebug() << "Clicked on item." << item->row() << " " << item->column()<<" "<<item->text();

		editArtist->clear();
		qDebug() << table->item(item->row(), 0)->text();
		editArtist->setText(table->item(item->row(), 0)->text());
		editTitlu->setText(table->item(item->row(), 1)->text());
		editGen->setText(table->item(item->row(), 2)->text());
		editDurata->setText(table->item(item->row(), 3)->text());

		});
	QObject::connect(table, &QTableWidget::itemSelectionChanged, [this]() {
		QList<QTableWidgetItem*> selectedItems = table->selectedItems();
		qDebug() << "Selected items:";
		for (QTableWidgetItem* item : selectedItems) {
			qDebug() << "Row:" << item->row() << ", Column:" << item->column() << ", Value:" << item->text();
			
		}
		qDebug() << "Done";
		});

	QObject::connect(sortBtn, &QPushButton::clicked, [this]() {
		if (sortArtistTitluRadio->isChecked())
			reloadData(srv.sortByArtistSong());
		else if (sortDurataRadio->isChecked())
			reloadData(srv.sortByDurata());
		else {
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString("You have to select a RadioButton."));
		}

		
		
});
	QObject::connect(filterBtn, &QPushButton::clicked, [this]() {
		qDebug() << filterOptionsCombo->currentIndex();
		QString filterText = editFiltru->text();
		qDebug() << filterText;
		QString filterOption = filterOptionsCombo->currentText();
		if (filterOption == "Gen")
			reloadData(srv.filtrareGen(filterText.toStdString()));
		else if (filterOption == "Durata") {
			
			QStringList parts = filterText.split("-");
			if (parts.size() == 2) {
				try {
					double startDuration = stod(parts.at(0).trimmed().toStdString()); // Remove leading and trailing whitespace
					double endDuration = stod(parts.at(1).trimmed().toStdString()); // Remove leading and trailing whitespace
					reloadData(srv.filtrareDurata(startDuration, endDuration));
				}
				catch (std::exception& ex) {
					QMessageBox::warning(nullptr, "Warning", QString::fromStdString("Cannot convert input to number."));
				}
				
			}
			else {
				// If the input string doesn't contain "-", treat it as a single string
				qDebug() << "Input string doesn't contain a delimiter.";
				QMessageBox::warning(nullptr, "Warning", QString::fromStdString("Not the required format for duration."));

			}
		}
		});

	QObject::connect(reloadInitialDataBtn, &QPushButton::clicked, this, [&]() {reloadData(srv.getAllSongs()); });
	QObject::connect(openPlaylistBtn, &QPushButton::clicked, this, [&]() {
		PlaylistGUI* playlistWindow = new PlaylistGUI{srv};
		playlistWindow->show();
		});
	QObject::connect(openPlaylistLabelBtn, &QPushButton::clicked, this, [&]() {
		PlayListLabelEditGUI* playlistLabelWindow = new PlayListLabelEditGUI{ srv.getPlaylist()};
		playlistLabelWindow->show();
		});
	QObject::connect(openPlaylistDrawBtn, &QPushButton::clicked, this, [&]() {
		PlaylistDrawGUI* playlistDrawGUI = new PlaylistDrawGUI{ srv.getPlaylist() };
		playlistDrawGUI->show();

		PlaylistDrawCirclesGUI* playlistDrawCirclesGUI = new PlaylistDrawCirclesGUI{ srv.getPlaylist() };
		playlistDrawCirclesGUI->show();
		});

}

void SongManagerGUI::reloadData(const vector<Song>& songs)
{
	table->setRowCount(songs.size());
	int row = 0;
	for (const auto& song : songs) {
		table->setItem(row, 0, new QTableWidgetItem{ QString::fromStdString(song.getArtist()) });
		table->setItem(row, 1, new QTableWidgetItem{ QString::fromStdString(song.getTitlu()) });
		table->setItem(row, 2, new QTableWidgetItem{ QString::fromStdString(song.getGen()) });
		table->setItem(row, 3, new QTableWidgetItem{ QString::fromStdString(std::to_string(song.getDurata())) });
		row++;
	}
}
