#ifndef __VIRTUAL_PLANET_H__
#define __VIRTUAL_PLANET_H__

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <exception>
#include <algorithm>

#include "Faction.hpp"
#include "Neutral_faction.hpp"

class World;

/*!
 * \brief Planète virtuelle
 *
 * Planète servant de base à toutes les autres.
 * Contient tous les paramètres communs
 */
class Virtual_planet
{
public:
    Virtual_planet(World&, unsigned, unsigned);		//Creation of random stat
    Virtual_planet(Virtual_planet*);
    virtual ~Virtual_planet() {}    //!< Destructeur à redéfinir

            void set_neighbourhood      ();	//generate neighbourhood
            void set_neighbourhood2     ();
    virtual void update_neighbourhood   (Virtual_planet *,Virtual_planet *); //update changes to neighbourhood when planet is attacked.
    virtual bool is_attacked            (Virtual_planet *)                  {return true; }	//!< Réponse lorsqu'une attaque est subie (vrai par défaut)
            void run                    ();
    virtual void reinitialisate_target  () {}                           //!< Réinitialisation de la cible, à redéfinir
            bool has_changed            ();
		virtual bool can_be_replaced				() {return true;}								//!< Renvoie true si la planete n'est pas un agent


  //Getter setter
    virtual char        display         () {return '.';}                //!< Caractère par défaut (point)
    virtual double      estimate_cost   () {return get_defense();}      //!< Estime le cout d'une attaque
    virtual std::string get_color_name  () {return "gray";}             //!< Couleur par défaut (gris)
    virtual Faction&    get_faction     ();
    virtual unsigned    pos_x           () {return pos_x_;}             //!< Ligne dans la grille
    virtual unsigned    pos_y           () {return pos_y_;}             //!< Colonne dans la grille
            World&      get_world       () {return world_;}             //!< Monde auquel appartient la planète
    virtual double      get_defense     () {return natural_defense_;}   //!< Défense de base
    virtual double      get_production  () {return production_rate_;}   //!< Productivité de base
    std::vector<Virtual_planet* > get_neighbourhood () {return neighbourhood_ ;}    //!< Liste des voisins


protected:
    void change ();

    World  & world_;    //!< Monde auquel appartient la planète
    unsigned pos_x_;	//!< Ligne dans la grille
    unsigned pos_y_;    //!< Colonne dans la grille

    std::vector<Virtual_planet* > neighbourhood_;   //!< Liste des voisins
    bool    changed_;   //!< Etat changé

    double  production_rate_;	//!< Taux de production entre MIN_PRODUCTION_RATE et MAX_PRODUCTION_RATE \see MIN_PRODUCTION_RATE \see MAX_PRODUCTION_RATE
    double  natural_defense_;	//!< Taux de défense naturelle entre MIN_NATURAL_DEFENSE et MAX_NATURAL_DEFENSE \see MIN_NATURAL_DEFENSE \see MAX_NATURAL_DEFENSE

    static const int MIN_PRODUCTION_RATE; //!< Taux de production minimal
    static const int MAX_PRODUCTION_RATE; //!< Taux de production maximal
    static const int MIN_NATURAL_DEFENSE; //!< Taux de défense naturelle minimal
    static const int MAX_NATURAL_DEFENSE; //!< Taux de défense naturelle maximal
};

std::ostream & operator<< (std::ostream &o, Virtual_planet &vp);

#endif
