#include <QApplication>
#include "gui.h"

int main(int argc, char** argv) {
    QApplication a{argc, argv};

    ClickableShapesWidget window;
    window.resize(400, 150);
    window.setWindowTitle("Clickable Shapes");
    window.show();

    return a.exec();
}