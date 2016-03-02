#include "qplanet.h"
/*!
 * \brief Initialise les pointeurs
 */
QPlanet::QPlanet() :
    ellipse_(nullptr),
    gold_(nullptr),
    shield_(nullptr),
    eco_(nullptr),
    defense_(nullptr)
{}

/*!
 * \brief Obtenir le disque représentant une planète
 * \return Ellipse Qt pour représenter la planète
 */
QGraphicsEllipseItem *QPlanet::getEllipse() const
{
    return ellipse_;
}

/*!
 * \brief Définit le disque représentant une planète
 * \param value disque créé à l'affichage
 */
void QPlanet::setEllipse(QGraphicsEllipseItem *value)
{
    ellipse_ = value;
}

/*!
 * \brief Obtenir l'image des sous!
 * \return Pixmap avec des pièces
 */
QGraphicsPixmapItem *QPlanet::getGold() const
{
    return gold_;
}

/*!
 * \brief Définir l'image des sous
 * \param value Image des sous générée à l'affichage
 */
void QPlanet::setGold(QGraphicsPixmapItem *value)
{
    gold_ = value;
}

/*!
 * \brief Obtenir l'image du bouclier
 * \return Pixmap avec un bouclier
 */
QGraphicsPixmapItem *QPlanet::getShield() const
{
    return shield_;
}

/*!
 * \brief Définir l'image du bouclier
 * \param value Image du bouclier générée à l'affichage
 */
void QPlanet::setShield(QGraphicsPixmapItem *value)
{
    shield_ = value;
}

/*!
 * \brief Obtenir la monnaie
 * \return Texte représentant la monnaie
 */
QGraphicsTextItem *QPlanet::getEco() const
{
    return eco_;
}

/*!
 * \brief Définir la monnaie
 * \param value Texte représentant la monnaie généré à l'affichage
 */
void QPlanet::setEco(QGraphicsTextItem *value)
{
    eco_ = value;
}

/*!
 * \brief Obtenir la défense de la planète
 * \return Texte représentant la défense
 */
QGraphicsTextItem *QPlanet::getDefense() const
{
    return defense_;
}
/*!
 * \brief Définir la défense de la planète
 * \param value Texte représentant la défense généré à l'affichage
 */
void QPlanet::setDefense(QGraphicsTextItem *value)
{
    defense_ = value;
}
