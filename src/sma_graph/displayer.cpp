#include "displayer.h"
#include "QPen"
#include "QBrush"

Displayer::Displayer(QMainWindow *mw):QWidget(mw),world_()
{
    world_.scheduler();
    size_planete = 20;

    setFixedSize(world_.len()*size_planete,world_.hei()*size_planete);
    m_scene = new QGraphicsScene(this);


    m_scene->setBackgroundBrush(QBrush(Qt::white));
    m_scene->setSceneRect(0,0,world_.len()*20,world_.hei()*20);         //Creer la scene

  //  thread = new QThread();

  //  connect(thread, SIGNAL(started()), worker, SLOT(doWork()));

    m_view = new QGraphicsView(m_scene,this);
    m_view->show();
}


void Displayer::afficherRect()
{
      m_scene->addRect(0,0,100,300,QPen(QColor("red")),QBrush(QColor("blue")));
}

void Displayer::display_world(){
    for(unsigned i=0;i<world_.len();i++){
        for(unsigned j=0;j<world_.hei();j++){
            m_scene->addEllipse(i*size_planete,
                                j*size_planete,
                                size_planete-2,
                                size_planete-2,
                                QPen(QColor(world_.get_grid(i,j)->get_faction().get_color_name())),
                                QBrush(QColor(world_.get_grid(i,j)->get_faction().get_color_name())));
        }
    }
}

bool Displayer::play(){
    bool play = !world_.isEnded();
    if (play) {
        world_.scheduler();
    }
    return play;
}

void Displayer::refresh()
{
    display_world();
    m_view->show();
}
