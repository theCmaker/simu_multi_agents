#ifndef FENETRE_H
#define FENETRE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include "../World.hpp"
#include "mainwindow.h"
#include <QThread>


class Displayer: public QWidget
{
public:
    Displayer(QMainWindow *);
    void afficherRect();
    void display_world();
    bool play();

private:
    QGraphicsScene *m_scene;
    QGraphicsView *m_view;

    World world_;
    int size_planete;

public slots:
    void refresh();
};

#endif // FENETRE_H
