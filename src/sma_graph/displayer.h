#ifndef FENETRE_H
#define FENETRE_H

#include "mainwindow.h"

#include "sstream"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QPen>
#include <QBrush>
#include <QTimer>
#include <QThread>
#include <QGraphicsTextItem>
#include <QMessageBox>

#include "../World.hpp"
#include "../Faction.hpp"



class Displayer: public QWidget
{
    Q_OBJECT
public:
    explicit Displayer(QWidget *parent = 0);
    Displayer(QMainWindow *);
    void afficherRect();
    void display_world();
    bool play();
    ~Displayer();

private:
    void end();

    QGraphicsScene *m_scene;
    QGraphicsView *m_view;

    World world_;
    unsigned size_planete_;
    unsigned len_text_box_;

    unsigned len_canvas_;
    unsigned hei_canvas_;

    int timerId;
    QTimer *timer;

    QString winning_faction_;

protected slots:
    void timerEvent();
    void refresh();
};

#endif // FENETRE_H
