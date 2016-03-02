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
#include "qplanet.h"



/**
 * @brief Zone d'affichage de l'application
 *
 * Cette classe gère l'affichage de l'application ainsi que le lancement du jeu.
 */
class Displayer: public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructeur par défaut
     *
     * @param parent Objet parent (conteneur par exemple)
     */
    explicit Displayer(QWidget *parent = 0);
    Displayer(QMainWindow *);

    void display_world();
    bool play();

    ~Displayer();

private:
    void end();
    void display_planet(unsigned posX, unsigned posY);

    //Vue
    QGraphicsScene *m_scene;    //!< Scène de l'affichage
    QGraphicsView *m_view;      //!< Vue
    QPlanet ** graph_grid_;     //!< Grille des objets affichés
    QGraphicsTextItem * text_panel_; //!< Panneau de texte latéral

    World world_;               //!< Plateau de jeu

    //Dimensions
    unsigned size_planete_;     //!< Taille d'une planète à l'affichage (px)
    unsigned len_text_box_;     //!< Largeur du panneau latéral (px)
    unsigned len_canvas_;       //!< Largeur du panneau graphique (px)
    unsigned hei_canvas_;       //!< Hauteur du panneau graphique (px)

    //Paramètres de jeu
    QTimer *timer;              //!< Chronomètre pour gérer la fréquence d'affichage
    QString winning_faction_;   //!< Nom de la faction gagnante

    //Visuels
    QPixmap shield_;            //!< Symbole bouclier
    QPixmap gold_;              //!< Symbole lingot

protected slots:
    void timerEvent();
    void refresh();
};

#endif // FENETRE_H
