#include <QtWidgets/QApplication>

#include <stdlib.h>
#include "UI.h"
#include "GUI.h"
#include <iostream>
using std::cout;
using std::endl;
void testAll() {
	testeDomain();
	cout << "Finished domain tests." << endl;
	testeRepo();
	testeFileRepo();
	cout << "Finished repo tests." << endl;
	testeService();
	cout << "Finished service tests." << endl;

}
void startApp(int argc, char* argv[]) {
	//SongRepository repo;
	SongRepositoryFile repoFile{"songs.txt"};
	
	SongValidator val;
	SongStore srv{ repoFile,val };
	//ConsoleUI ui{ srv };

	//ui.run();
	 
	QApplication a(argc, argv);
    SongManagerGUI gui{ srv };
	gui.show();
	a.exec();
}
int main(int argc, char* argv[]) {
	testAll();
	startApp(argc, argv);
	//_CrtDumpMemoryLeaks();
	return 0;

}