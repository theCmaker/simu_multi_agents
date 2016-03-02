#ifndef QPLANET_H
#define QPLANET_H

#include <QGraphicsView>

/*!
 * \brief Gestion d'affichage de planète
 *
 * Conserve des pointeurs vers les planètes affichées, de manière à les remplacer quand elles ont changé.
 */
class QPlanet
{
public:
    QPlanet();

    QGraphicsEllipseItem *getEllipse() const;
    void setEllipse(QGraphicsEllipseItem *value);

    QGraphicsPixmapItem *getGold() const;
    void setGold(QGraphicsPixmapItem *value);

    QGraphicsPixmapItem *getShield() const;
    void setShield(QGraphicsPixmapItem *value);

    QGraphicsTextItem *getEco() const;
    void setEco(QGraphicsTextItem *value);

    QGraphicsTextItem *getDefense() const;
    void setDefense(QGraphicsTextItem *value);

private:
    QGraphicsEllipseItem * ellipse_; //!< Disque représentant une planète
    QGraphicsPixmapItem  * gold_;    //!< Image or
    QGraphicsPixmapItem  * shield_;  //!< Image bouclier
    QGraphicsTextItem    * eco_;     //!< Monnaie
    QGraphicsTextItem    * defense_; //!< Défense
};

#endif // QPLANET_H
