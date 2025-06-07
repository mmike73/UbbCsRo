#pragma once
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QListWidget>
#include <QMessageBox>
#include <QPainter>
#include "Service.h"
class PlaylistGUI:public QWidget,public Observer {
private:
	SongStore& srv;
	QHBoxLayout* mainLayout;
	QWidget* leftWidget;
	QVBoxLayout* leftLayout;

	QFormLayout* addFormLayout;
	QWidget* addFormWidget;
	QLabel* labelArtist, *labelTitle;
	QLineEdit* editArtist, * editTitle;
	QPushButton* addByArtistTitleBtn;
	QSlider* sliderAddRandom;
	QLineEdit* editValueSlider;
	QPushButton* addRandomBtn;
	QPushButton* clearPlaylistBtn;
	QPushButton* closeWindowBtn;

	QListWidget* songList;

	void initializeGUIComponents();
	void connectSignalsSlots();
	void addByTitleAndArtist();
	void reloadData(const vector<Song>& playlistSongs);
public:
	PlaylistGUI(SongStore& _srv) : srv{ _srv } {
		initializeGUIComponents();
		connectSignalsSlots();
		reloadData(srv.getPlaylistSongs());
	};
	
};

class PlayListLabelEditGUI : public QWidget, public Observer {
private:
	QHBoxLayout* layout;
	QLabel* lbl;
	QLineEdit* edit;
	Playlist& playlist;
public:
	PlayListLabelEditGUI(Playlist& _playlist) : playlist{ _playlist } {
		lbl = new QLabel{ "Numar melodii:" };
		edit = new QLineEdit;
		layout = new QHBoxLayout;
		setLayout(layout);
		layout->addWidget(lbl);
		layout->addWidget(edit);
		lbl->setFont(QFont{ "arial", 24 });
		playlist.addObserver(this);
		setAttribute(Qt::WA_DeleteOnClose);
		update();
	}
	void update() override {
		QString numarMelodii = QString::fromStdString(std::to_string(playlist.getAllPlaylistSongs().size()));
		edit->setText(numarMelodii);
	}
	
	~PlayListLabelEditGUI() {
		playlist.removeObserver(this);
	}
};

class PlaylistDrawGUI : public QWidget, public Observer {
private:
	Playlist& playlist;
public:
	
	void paintEvent(QPaintEvent*) override {
		QPainter p{ this };
		int x = 0;
		int y = 0;
		for (auto song : playlist.getAllPlaylistSongs()) {
			p.drawRect(x, y, 10, song.getDurata() * 10);
			x += 40;

		}
	}
public:
	PlaylistDrawGUI(Playlist& _playlist) : playlist{ _playlist } {
		playlist.addObserver(this);
		setAttribute(Qt::WA_DeleteOnClose);

		update();
	};
	void update() override {
		repaint();
	}
	~PlaylistDrawGUI() {
		playlist.removeObserver(this);
	}
	
	
};

//exemplu de desenare cercuri
class PlaylistDrawCirclesGUI : public QWidget, public Observer {
private:
	Playlist& playlist;
public:
	void paintEvent(QPaintEvent*) override {
		QPainter p{ this };
		
		//draw circles with radius equal to duration
		
		int count = 1;
		QList<QColor> colorList{Qt::blue, Qt::magenta, Qt::green, Qt::yellow, Qt::red};
		
		for (auto song : playlist.getAllPlaylistSongs()) {
			int x_pos = rand()%400+1;
			int y_pos = rand()%400+1;
			double duration = song.getDurata();
			p.setBrush(QBrush(colorList.at(count % 5)));
			p.drawEllipse(x_pos, y_pos, duration*10, duration*10);
			count++;
		}
	}
public:
	PlaylistDrawCirclesGUI(Playlist& _playlist) : playlist{ _playlist } {
		playlist.addObserver(this);
		setAttribute(Qt::WA_DeleteOnClose);
		update();
	};
	void update() override {
		repaint();
	}
	~PlaylistDrawCirclesGUI() {
		playlist.removeObserver(this);
	}


};