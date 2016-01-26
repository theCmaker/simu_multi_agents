#ifndef __WORLD_H__
#define __WORLD_H__

#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <algorithm>    // std::random_shuffl

#include <chrono>
#include <thread>

#include "Mother_land.hpp"
#include "Virtual_planet.hpp"
#include "Colonized_planet.hpp"
#include "Faction.hpp"

using namespace std;
typedef unsigned time_h; /* Simulation time */

class World
{
public:
  World(std::mt19937&, unsigned len=20, unsigned hei=20);
	~World();

  time_h start();			//return duration of simulation
  void scheduler();		//manage action of agents

	void display();			//Display at a time X

	int gen_mt();
  int gen_mt(int a, int b);
	int gen_mt_shuffle(int i);

	//Getter/setter 
	Virtual_planet* get_grid(unsigned x, unsigned y);
	void set_grid(Virtual_planet*, unsigned x, unsigned y);
	unsigned len() const { return len_; }
	unsigned hei() const { return hei_; }

	void add_waiting_agent(Colonized_planet*);
	void remove_waiting_agent(Colonized_planet*);

	Faction& get_neutral_faction();

	void kill_faction(Faction&);
private:
	bool DEBUG = true;

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
	std::mt19937& gen_mt_;

	//Faction neutre
	Faction neutral_faction_;
};

#endif
