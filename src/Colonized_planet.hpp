#ifndef __COLONIZED_PLANET_H__
#define __COLONIZED_PLANET_H__

#include "Free_planet.hpp"

/**
 * @brief Planète colonisée
 *
 * Une planète colonisée est une planète possédée par une faction
 */
class Colonized_planet : public Virtual_planet
{
public:
    Colonized_planet (World &, unsigned, unsigned, Faction&);
    Colonized_planet (Virtual_planet *, Faction&);
    ~Colonized_planet () {}

    void update_neighbourhood   (Virtual_planet *, Virtual_planet *);   //update changes to neighbourhood when planet is attacked.
    bool attack 				(Virtual_planet *);                     //bool : success
    virtual bool is_attacked 	(Virtual_planet *);

    void convert_to_free_planet         ();

    Faction        &get_faction		();
    double          get_defense		();
    double          get_production  ();
    Virtual_planet *get_target		() {return target_;}

    void 		demand_to_faction		(double);	//Execute a demande of money
    double      estimate_cost		 	();         //Estimate the cost of the colonization (and attack)
    void 		add_to_budget			(double);
    void 		reinitialisate_target	();

    char 		display                 () {return faction_.get_colony_symbol();}
    std::string get_color_name          () {return faction_.get_colony_color_name();}
    void        run                     ();
		bool can_be_replaced() { return false; }								//!< Renvoie true si la planete n'est pas un agent

protected:
    double      	colony_defense_;    //!< Valeur de défense
    double          colony_production_; //!< Valeur de production de monnaie
    Faction        &faction_;           //!< Faction à laquelle appartient la colonie

    Virtual_planet *target_;            //!< Planète ciblée par une éventuelle attaque
    double 			budget_;            //!< Argent disponible
    double 			demand_;            //!< Coût estimé d'une opération

    static const int MAX_COLONY_DEFENSE;    //!< Valeur de défense maximum
    static const int MAX_COLONY_PRODUCTION; //!< Valeur de production maximum
    static const int COLONY_MULTIPLICATOR;  //!< Facteur de production
};

#endif
