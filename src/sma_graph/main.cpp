#include "mainwindow.h"
#include <QApplication>
#include "mainwindow.h"
#include "QGraphicsScene"
#include "displayer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Displayer fenetre;
    fenetre.show();

    fenetre.display_world();

    return a.exec();
}
