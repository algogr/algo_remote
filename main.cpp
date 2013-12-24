#include <QtGui/QApplication>
#include "remote.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Remote w;
    //w.setStyleSheet("QWidget {background-image: url(algologo-1.png) }");
    w.setStyleSheet("background-image: url(:/suspects.png)");
    w.show();
    
    return a.exec();
}
