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
  World();
  World(std::string);
  ~World();

  time_h simulate();
  void scheduler();

private:
  std::vector<std::vector<Virtual_planet> > grid_;
  std::list<Faction> factions_;
  std::vector<Colonized_planet *> waiting_agents_;     /* Swapped with already_run_agents_ for each step */
  std::vector<Colonized_planet *> already_run_agents_;
  unsigned steps_;
  unsigned nb_simulated_agents_;

};

#endif /* end of include guard: __WORLD_H__ */
