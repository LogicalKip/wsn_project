#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(time(NULL));
    MainWindow w(new Game);
    w.show();

   //FIXME check for destruct calls missing


    return a.exec();
}
