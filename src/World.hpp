#ifndef __WORLD_H__
#define __WORLD_H__

#include <iostream>
#include <vector>
#include <list>
#include <random>

#include "Faction.hpp"
#include "Virtual_planet.hpp"
#include "Colonized_planet.hpp"

std::mt19937 generator(123);

typedef unsigned time_h; /* Simulation time */

class World
{
public:
  World(std::mt19937&, unsigned len=20, unsigned hei=20);
  ~World();

  time_h start();			//return duration of simulation
  void scheduler();		//manage action of agents

	int mt();
	//Getter/setter 
	Virtual_planet* grid(unsigned x, unsigned y);
	unsigned len() const { return len_ };
	unsigned hei() const { return hei_ };

private:
  //private methods
	void generate_world();

  //Containers
  std::vector< std::vector <Virtual_planet *> > grid_;
  std::list< Faction > factions_;
  
  //Access
  std::vector<Colonized_planet &> waiting_agents_;     /* Swapped with already_run_agents_ for each step */
  std::vector<Colonized_planet &> already_run_agents_;
  
  //Stats
  unsigned steps_;
  unsigned nb_simulated_agents_;

  //Dimension of the world
  unsigned len_;
  unsigned hei_;

	//mt
	std::mt19937& gen_mt_;

};

#endif /* end of include guard: __WORLD_H__ */
