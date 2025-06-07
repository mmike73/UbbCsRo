#include "PlaylistGUI.h"

void PlaylistGUI::initializeGUIComponents()
{
	mainLayout = new QHBoxLayout;
	this->setLayout(mainLayout);
	QWidget* leftWidget = new QWidget;
	leftLayout = new QVBoxLayout;
	leftWidget->setLayout(leftLayout);

	addFormLayout = new QFormLayout;
	addFormWidget = new QWidget;
	addFormWidget->setLayout(addFormLayout);
	labelArtist = new QLabel{ "Artist" };
	labelTitle = new QLabel{ "Titlu" };
	editArtist = new QLineEdit;
	editTitle = new QLineEdit;
	addByArtistTitleBtn = new QPushButton{ "Adaugare dupa artist si titlu" };
	addFormLayout->addRow(labelArtist, editArtist);
	addFormLayout->addRow(labelTitle, editTitle);
	addFormLayout->addWidget(addByArtistTitleBtn);

	leftLayout->addWidget(addFormWidget);

	sliderAddRandom = new QSlider;
	sliderAddRandom->setMaximum(100);
	sliderAddRandom->setMinimum(1);
	editValueSlider = new QLineEdit;
	

	addRandomBtn = new QPushButton{ "Adaugare melodii random" };
	leftLayout->addWidget(sliderAddRandom);
	leftLayout->addWidget(editValueSlider);
	leftLayout->addWidget(addRandomBtn);
	clearPlaylistBtn = new QPushButton{ "Golire playlist" };
	leftLayout->addWidget(clearPlaylistBtn);

	closeWindowBtn = new QPushButton{ "Inchidere fereastra" };
	leftLayout->addWidget(closeWindowBtn);

	mainLayout->addWidget(leftWidget);
	
	songList= new QListWidget;
	mainLayout->addWidget(songList);
}

void PlaylistGUI::connectSignalsSlots() {
	QObject::connect(addByArtistTitleBtn, &QPushButton::clicked, this, &PlaylistGUI::addByTitleAndArtist);
	QObject::connect(sliderAddRandom, &QSlider::valueChanged, this, [&]() {
		editValueSlider->setText(QString::fromStdString(std::to_string(sliderAddRandom->value())));
		});
	QObject::connect(addRandomBtn, &QPushButton::clicked, this, [&]() {
		int sliderValue = sliderAddRandom->value();
		srv.addRandomToPlaylist(sliderValue);
		reloadData(srv.getPlaylistSongs());
		});
	QObject::connect(clearPlaylistBtn, &QPushButton::clicked, this, [&]() {
		srv.emptyPlayList();
		reloadData(srv.getPlaylistSongs());
	});
	QObject::connect(closeWindowBtn, &QPushButton::clicked, this, [&]() {
		this->close();
		});

}
void PlaylistGUI::addByTitleAndArtist()
{
	QString title = editTitle->text().trimmed();
	QString artist = editArtist->text().trimmed();

	try {
		srv.addToPlaylist(title.toStdString(), artist.toStdString());
		reloadData(srv.getPlaylistSongs());
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}

}



void PlaylistGUI::reloadData(const vector<Song>& playlistSongs)
{
	songList->clear();

	for (auto& song : playlistSongs) {
		songList->addItem(QString::fromStdString(song.toString()));
	}
}
