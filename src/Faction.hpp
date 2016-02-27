#ifndef __FACTION_H__
#define __FACTION_H__

#include <string>
#include <list>
#include <sstream>

class World;
class Mother_land;
class Colonized_planet;

/*!
 * \brief Entité de jeu, ensemble de planètes
 *
 * Une faction est un groupement de colonies. Une faction est dirigée par une planète mère.
 *
 * \note La mort de la planète mère induit la mort de la faction.
 */
class Faction
{
private:
    World&							world_;                 //!< Monde auquel est rattachée la faction
    std::string						name_;                  //!< Nom de la faction
    double							money_;                 //!< Argent possédé par la faction
    Mother_land					*	motherland_;            //!< Planète qui gère la faction
    char                            motherland_symbol_;     //!< Caractère représentant la planète mère
    std::list<Colonized_planet*>    colonies_;              //!< Liste des colonies de la faction
    char                            colony_symbol_;         //!< Caractère représentant les colonies
    std::string                     colony_color_name_;     //!< Nom de la couleur représentant la colonie (x11names)
    std::string                     motherland_color_name_; //!< Nom de la couleur représentant la planète mère (x11names)

    std::list<std::pair<Colonized_planet*, double> > demands_;  //!< Liste des demandes de fonds associées à la planète demandeuse

    //stats
    double  money_spent_;           //!< Argent dépensé
    double  money_produce_;         //!< Argent généré
    int     nb_successful_attack_;  //!< Attaques réussies
    int     nb_failed_attack_;      //!< Attaques échouées

public:
	Faction(World& world, std::string name = "default", Mother_land* = nullptr);	//Create a faction and convert a free planete into a mother land
    Faction& operator= (Faction) {return *this;}    //!< Opérateur d'affectation, sans effet

    //Comparators
    bool operator== (const Faction &other) const {return this->name_ == other.name_;}   //!< Comparateur avec une autre faction
    bool operator== (Faction &other)             {return this->name_ == other.name_;}   //!< Comparateur avec une autre faction
  
    //Actions
    Faction * run();
    void      init();
    void      die();

	//Getters
    std::string   get_name                     () {return name_;}                   //!< Nom de la colonie
    double        get_money                    () {return money_;}                  //!< Argent disponible
    char          get_motherland_symbol        () {return motherland_symbol_;}      //!< Caractère représentant la planète mère
    char          get_colony_symbol            () {return colony_symbol_;}          //!< Caractère représentant une colonie
    std::string   get_colony_color_name        () {return colony_color_name_;}      //!< Couleur x11 des colonies
    std::string   get_motherland_color_name    () {return motherland_color_name_;}  //!< Couleur x11 de la planète mère
    Mother_land*  get_motherland_              () {return motherland_;}             //!< Planète mère
    std::list<Colonized_planet*> & get_colonies() {return colonies_;}               //!< Liste des colonies

    //Methods
    void add_colony          (Colonized_planet* colony) {colonies_.push_back(colony);} //!< Ajoute une colonie à la faction
	void remove_colony       (Colonized_planet* colony);
	void remove_mother_land  ();
	void remove_demand       (Colonized_planet* colony);
    void add_to_banque       (double);

    //Setters
    void set_colony_symbol        (char c)                            {colony_symbol_ = c;}                             //!< Définit le caractère représentant une colonie
    void set_motherland_symbol    (char c)                            {motherland_symbol_ = c;}                         //!< Définit le caractère représentant la planète mère
    void set_colony_color_name    (std::string colony_color_name)     {colony_color_name_ = colony_color_name;}         //!< Définit la couleur des colonies
    void set_motherland_color_name(std::string motherland_color_name) {motherland_color_name_ = motherland_color_name;} //!< Définit la couleur de la planète mère
	void add_demand               (Colonized_planet*, double);

    //stat
    double  get_money_spent           () {return money_spent_;}             //!< Argent dépensé
    double  get_money_produce_        () {return money_produce_;}           //!< Argent généré
    int     get_nb_successful_attack_ () {return nb_successful_attack_;}    //!< Attaques réussies
    int     get_nb_failed_attack_     () {return nb_failed_attack_;}        //!< Attaques échouées
    void    inc_nb_successful_attack_ ();
    void    inc_nb_failed_attack_     ();

    //Display
    std::string toString();
};

/*!
 * \brief Comparateur de planètes colonisées
 */
class Comparator {
private:
    Colonized_planet* colonized_planet_;        //!< Planète qui doit servir de base pour la comparaison
public:
    /*!
     * \brief Constructeur
     * \param colonized_planet planète servant d'élément de comparaison
     */
    Comparator(Colonized_planet* colonized_planet) {
        colonized_planet_ = colonized_planet;
    }

    /*!
     * \brief Comparaison avec la planète de base
     * \param pair_colony une paire dont le premier membre est comparé avec la planète de base
     * \return Booléen à vrai si la comparaison est valide
     */
    bool operator()(std::pair<Colonized_planet*,double> pair_colony) {
        return pair_colony.first == colonized_planet_;
    }
};
#endif
