#ifndef __WORLD_H__
#define __WORLD_H__

#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <algorithm>    // std::random_shuffl
#include <sstream>

/*#include <chrono>
#include <thread>*/

#include "Mother_land.hpp"
#include "Virtual_planet.hpp"
#include "Colonized_planet.hpp"
#include "Faction.hpp"

using namespace std;
typedef unsigned time_h; /* Simulation time */

class World
{
public:
    World(unsigned len=20, unsigned hei=20);
	~World();

    time_h start();			//return duration of simulation
    void scheduler();		//manage action of agents

	void display();			//Display at a time X

    //Gestion des agents
    void remove_faction(Faction*);
    void add_waiting_agent(Colonized_planet*);
    void remove_waiting_agent(Colonized_planet*);

    //Fonction d'alea
	static int gen_mt();
	static int gen_mt(int a, int b);
	static int gen_mt_shuffle(int i);

	//Getter/setter 
	Virtual_planet* get_grid(unsigned x, unsigned y);
	void set_grid(Virtual_planet*, unsigned x, unsigned y);
	unsigned len() const { return len_; }
	unsigned hei() const { return hei_; }
	Faction& get_neutral_faction();
    std::list<Faction> get_factions();
    bool isEnded() {return end_;}

    //display
    string stats();
    string get_winner_name();

private:
    const static bool DEBUG=true;
    bool end_;

  //private methods
	void generate_world();

  //Containers
  std::vector< std::vector <Virtual_planet* > > grid_;
  std::list< Faction > factions_;
  
  //Access
  std::vector<Colonized_planet * > waiting_agents_;     /* Swapped with already_run_agents_ for each step */
  std::vector<Colonized_planet * > already_run_agents_;
  
  //Stats
  unsigned steps_;
  unsigned nb_simulated_agents_;

  //Dimension of the world
  unsigned len_;
  unsigned hei_;

	//mt
	static std::mt19937 gen_mt_;

	//Faction neutre
	Faction neutral_faction_;
};

#endif
