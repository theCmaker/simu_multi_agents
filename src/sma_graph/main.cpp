#include "mainwindow.h"
#include <QApplication>
#include "../World.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    World w1;

    MainWindow w;
    w.show();

    return a.exec();
}
