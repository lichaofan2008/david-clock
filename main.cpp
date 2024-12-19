#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("David");
    a.setApplicationName("QtClock");
    MainWindow w;
    w.showFullScreen();
    //w.show();
    return a.exec();
}
