#ifndef FENETRE_H
#define FENETRE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include "../World.hpp"

#include <QThread>


class Displayer: public QWidget
{
public:
    Displayer();
    void afficherRect();
    void display_world();
    void exec();
private:
    QGraphicsScene *m_scene;
    QGraphicsView *m_view;

    World world_;
    int size_planete;
};

#endif // FENETRE_H
