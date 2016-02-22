#include "displayer.h"

Displayer::Displayer(QMainWindow *mw):QWidget(mw),world_(),size_planete_(25),len_text_box_(150),
    winning_faction_("[Displayer]nofaction"),
    shield_("../../res/shield.png"),
    gold_("../../res/gold.png")

{
    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timerEvent()));
    timer->start(1000);

    world_.scheduler();

    len_canvas_= world_.len()*size_planete_;
    hei_canvas_= world_.hei()*size_planete_;

    setFixedSize(len_canvas_ + len_text_box_, hei_canvas_);


    m_scene = new QGraphicsScene(this);


    m_scene->setBackgroundBrush(QBrush(Qt::white));
    m_scene->setSceneRect(0,0,len_canvas_ + len_text_box_, hei_canvas_);         //Creer la scene

    m_view = new QGraphicsView(m_scene,this);
    m_view->show();
}

Displayer::~Displayer(){
    delete timer;
    delete m_scene;
    delete m_view;
}


void Displayer::afficherRect()
{
      m_scene->addRect(0,0,100,300,QPen(QColor("red")),QBrush(QColor("blue")));
}

void Displayer::display_world(){
    QGraphicsPixmapItem *pm;
     QGraphicsTextItem *text;
    for(unsigned i=0;i<world_.len();i++){
        for(unsigned j=0;j<world_.hei();j++){
            //Display planet
            m_scene->addEllipse(i*size_planete_,
                                j*size_planete_,
                                size_planete_-2,
                                size_planete_-2,
                                QPen(QColor(world_.get_grid(i,j)->get_color_name())),
                                QBrush(QColor(world_.get_grid(i,j)->get_color_name())));

            //Display eco (bottom left)
            pm = m_scene->addPixmap(gold_);
            pm->setPos(i*size_planete_,j*size_planete_+size_planete_-15);
            text = m_scene->addText(QString(std::to_string((long double)world_.get_grid(i,j)->get_production()).c_str()),
                                                       QFont("Times", 5, QFont::Bold));
            text->setPos(i*size_planete_,j*size_planete_+size_planete_-15);

            //Display def (bottom right)
            pm = m_scene->addPixmap(shield_);
            pm->setPos(i*size_planete_+size_planete_-12,j*size_planete_+size_planete_-15);
            text = m_scene->addText(QString(std::to_string((long double)world_.get_grid(i,j)->get_defense()).c_str()),
                                                       QFont("Times", 5, QFont::Bold));
            text->setPos(i*size_planete_+size_planete_-12,j*size_planete_+size_planete_-15);


        }
    }

    m_scene->addRect(len_canvas_,0,len_text_box_,hei_canvas_,QPen(Qt::black),QBrush(Qt::white));
    text = m_scene->addText(world_.stats().c_str());
    text->setPos(len_canvas_+2,2);
}

void Displayer::timerEvent()
{
    if (play()) {
        refresh();
    } else {
        timer->stop();
    }
}

bool Displayer::play(){
    bool play = !world_.isEnded();
    if (play) {
        world_.scheduler();
    }else{
        winning_faction_ = QString(world_.get_winner_name().c_str());
        end();
    }
    return play;
}

void Displayer::refresh()
{
    display_world();
    m_view->show();
}

void Displayer::end(){
    QMessageBox msgBox;
    QString str("La faction " );
    str += winning_faction_;
    str += " a gagne \n";
    msgBox.setText(str);
    msgBox.exec();
}
