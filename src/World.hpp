#ifndef __WORLD_H__
#define __WORLD_H__

#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <algorithm>    // std::random_shuffle
#include <sstream>

#include "Mother_land.hpp"
#include "Virtual_planet.hpp"
#include "Colonized_planet.hpp"
#include "Faction.hpp"

using namespace std;
/*!
 * \brief Unité de temps utilisée pour la simulation
 */
typedef unsigned time_h; /* Simulation time */

/*!
 * \brief Monde du jeu, possédant la grille
 */
class World
{
public:
    World(unsigned len = 20, unsigned hei = 20);
	~World();

    time_h  start           ();		//return duration of simulation
    void    scheduler       ();		//manage action of agents
    void    test2factions   ();
    void    test3factions   ();
    void    test4factions   ();

    void    display         ();		//Display at a time X

    //Gestion des agents
    void remove_faction         (Faction*);
    void add_waiting_agent      (Colonized_planet*);
    void remove_waiting_agent   (Colonized_planet*);

    //Fonction d'alea
    static int  gen_mt          ();
    static int  gen_mt          (int a, int b);
    static int  gen_mt_shuffle  (int i);
    static void dispose         ();

	//Getter/setter 
	Virtual_planet* get_grid(unsigned x, unsigned y);
    void            set_grid(Virtual_planet*, unsigned x, unsigned y);
    unsigned        len     () const {return len_;} //!< Nombre de places sur une ligne
    unsigned        hei     () const {return hei_;} //!< Nombre de places sur une colonne
    bool            isEnded ()       {return end_;} //!< Vrai si la partie est terminée
    std::list<Faction> get_factions();

    //display
    string stats();
    string get_winner_name();

private:
    const static bool DEBUG = true; //!< Constante de débogage
                 bool end_;         //!< Fin de la partie

    //Containers
    std::vector< std::vector <Virtual_planet* > > grid_;    //!< Grille de jeu
    std::list< Faction > factions_;                         //!< Liste des factions en jeu

    //Access
    std::vector<Colonized_planet * > waiting_agents_;       //!< Liste des agents n'ayant pas encore joué \note Echangé avec already_run_agents_ à chaque tour \see already_run_agents_
    std::vector<Colonized_planet * > already_run_agents_;   //!< Liste des agents ayant déjà joué

    //Stats
    unsigned steps_;                //!< Nombre de tours
    unsigned nb_simulated_agents_;  //!< Nombre d'agents

    //Dimension of the world
    unsigned len_;                  //!< Nombre de places par ligne
    unsigned hei_;                  //!< Nombre de places par colonne

	//mt
    static std::mt19937 gen_mt_;    //!< Générateur aléatoire
};

#endif
