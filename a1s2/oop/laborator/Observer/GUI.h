#pragma once
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QGroupBox>
#include <QComboBox>

#include <QTableWidget>
#include <QListWidget>
#include <QMessageBox>
#include "Service.h"
#include "PlaylistGUI.h"

class SongManagerGUI : public QWidget {
private:
	SongStore& srv;

	QHBoxLayout* mainLayout;

	QWidget* leftWidget;
	QVBoxLayout* leftSideLayout;

	QWidget* rightWidget;
	QVBoxLayout* rightSideLayout;

	QWidget* addWidget;
	QFormLayout* addWidgetLayout;
	QLabel* lblTitlu;
	QLineEdit* editTitlu;
	
	QLabel* lblArtist;
	QLineEdit* editArtist;

	QLabel* lblGen;
	QLineEdit* editGen;

	QLabel* lblDurata;
	QLineEdit* editDurata;

	QPushButton* addBtn;

	QGroupBox* sortGroupBox;
	QVBoxLayout* sortLayout;

	QRadioButton* sortDurataRadio;
	QRadioButton* sortArtistTitluRadio;
	QPushButton* sortBtn;

	QWidget* filterWidget;
	QFormLayout* filterLayout;
	QLabel* lblFiltru;
	QLineEdit* editFiltru;
	QComboBox* filterOptionsCombo;
	QPushButton* filterBtn;
	QPushButton* reloadInitialDataBtn;

	QPushButton* openPlaylistBtn;
	QPushButton* openPlaylistLabelBtn;
	QPushButton* openPlaylistDrawBtn;
	QTableWidget* table;

	void initializeGUIComponents();
	void connectSignalsSlots();
	void reloadData(const vector<Song>& songs);
public:
	SongManagerGUI(SongStore& _srv) : srv{ _srv } {
		initializeGUIComponents();
		connectSignalsSlots();
		reloadData(srv.getAllSongs());
	}

};