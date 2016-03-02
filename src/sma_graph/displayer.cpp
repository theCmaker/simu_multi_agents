#include "displayer.h"

/*!
 * \brief Crée l'interface visuelle de présentation de la grille de simulation
 * \param mw Objet graphique Qt parent
 */
Displayer::Displayer(QMainWindow *mw):QWidget(mw),world_(),size_planete_(25),len_text_box_(180),
    winning_faction_("[Displayer]nofaction"),
    shield_("../../res/shield.png"),
    gold_("../../res/gold.png")
{
    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timerEvent()));
    timer->start(1);

    world_.test2factions();
    //world_.test3factions();
    //world_.test4factions();
    world_.scheduler();

    graph_grid_ = new QPlanet*[world_.len()];
    for (unsigned i = 0; i < world_.len(); ++i) {
        graph_grid_[i] = new QPlanet[world_.hei()];
    }

    len_canvas_= world_.len()*size_planete_;
    hei_canvas_= world_.hei()*size_planete_;

    setFixedSize(len_canvas_ + len_text_box_, hei_canvas_);

    m_scene = new QGraphicsScene(this);

    m_scene->setBackgroundBrush(QBrush(Qt::white));
    m_scene->setSceneRect(0,0,len_canvas_ + len_text_box_, hei_canvas_);         //Creer la scene
    m_scene->addRect(len_canvas_,0,len_text_box_,hei_canvas_,QPen(Qt::black),QBrush(Qt::white)); //Ajoute le panneau de droite

    text_panel_ = m_scene->addText(world_.stats().c_str());
    text_panel_->setPos(len_canvas_ + 2,2);

    m_view = new QGraphicsView(m_scene,this);
    m_view->show();
}

/*!
 * \brief Supprime et nettoie l'interface visuelle de présentation de la grille de simulation
 */
Displayer::~Displayer(){
    delete timer;
    delete m_scene;
    delete m_view;
    for (unsigned i = 0; i < world_.len(); ++i) {
        delete graph_grid_[i];
    }
    delete graph_grid_;
}

/*!
 * \brief Affiche la grille
 */
void Displayer::display_world(){
    for(unsigned i=0;i<world_.len();i++){
        for(unsigned j=0;j<world_.hei();j++){
            if(world_.get_grid(i,j)->has_changed()){
                display_planet(i,j);
            }
        }
    }

    text_panel_->setPlainText(QString(world_.stats().c_str()));
}

/*!
 * \brief Affiche une planète
 * \param posX Position X de la planète
 * \param posY Position Y de la planète
 * \note  Position X = 0, Y = 0 en haut à gauche
 */
void Displayer::display_planet(unsigned posX, unsigned posY){
    QGraphicsPixmapItem *pm;
    QGraphicsTextItem *text;
    unsigned pos_to_set_icon = size_planete_/2 - 5;
    //Remove old item if necessary
    if (graph_grid_[posX][posY].getEllipse() != nullptr) {
        m_scene->removeItem(graph_grid_[posX][posY].getEllipse());
        delete graph_grid_[posX][posY].getEllipse();
        m_scene->removeItem(graph_grid_[posX][posY].getGold());
        delete graph_grid_[posX][posY].getGold();
        m_scene->removeItem(graph_grid_[posX][posY].getShield());
        delete graph_grid_[posX][posY].getShield();
        m_scene->removeItem(graph_grid_[posX][posY].getEco());
        delete graph_grid_[posX][posY].getEco();
        m_scene->removeItem(graph_grid_[posX][posY].getDefense());
        delete graph_grid_[posX][posY].getDefense();
    }
    //Display planet
    graph_grid_[posX][posY].setEllipse(
        m_scene->addEllipse(posX*size_planete_,
                            posY*size_planete_,
                            size_planete_-2,
                            size_planete_-2,
                            QPen(QColor(world_.get_grid(posX,posY)->get_color_name().c_str())),
                            QBrush(QColor(world_.get_grid(posX,posY)->get_color_name().c_str()))));

    //Display eco (bottom left)
    pm = m_scene->addPixmap(gold_);
    pm->setPos(posX*size_planete_ + pos_to_set_icon,posY*size_planete_);
    graph_grid_[posX][posY].setGold(pm);

    text = m_scene->addText(QString(std::to_string((long long)(world_.get_grid(posX,posY)->get_production())).c_str()),
                                               QFont("Arial", 7, QFont::Bold));
    text->setPos(posX*size_planete_ + pos_to_set_icon-5,posY*size_planete_);
    text->setDefaultTextColor(Qt::white);
    graph_grid_[posX][posY].setEco(text);

    //Display def (bottom right)
    pm = m_scene->addPixmap(shield_);
    pm->setPos(posX*size_planete_ + pos_to_set_icon,posY*size_planete_+size_planete_-10);
    graph_grid_[posX][posY].setShield(pm);
    text = m_scene->addText(QString(std::to_string((long long)(world_.get_grid(posX,posY)->get_defense())).c_str()),
                                               QFont("Arial", 7, QFont::Bold));
    text->setPos(posX*size_planete_ + pos_to_set_icon-5,posY*size_planete_+size_planete_-15);
    text->setDefaultTextColor(Qt::white);
    graph_grid_[posX][posY].setDefense(text);
}

/*!
 * \brief Evènement de mise à jour de l'affichage
 */
void Displayer::timerEvent()
{
    if (play()) {
        refresh();
    } else {
        timer->stop();
    }
}

/*!
 * \brief Teste si la partie n'est pas finie
 * \return Etat du jeu (true -> en cours, false -> fini)
 */
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

/*!
 * \brief Commande de rafraichissement de l'affichage
 */
void Displayer::refresh()
{
    display_world();
    m_view->show();
}

/*!
 * \brief Affiche la faction gagnante dans une boîte à message
 */
void Displayer::end(){
    QMessageBox msgBox;
    QString str("La faction " );
    str += winning_faction_;
    str += " a gagne \n";
    msgBox.setText(str);
    msgBox.exec();
}
