#ifndef __VIRTUAL_PLANET_H__
#define __VIRTUAL_PLANET_H__

#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "Faction.hpp"

class World;

class Virtual_planet
{
public:
  Virtual_planet(World&, unsigned, unsigned);		//Creation of random stat
	Virtual_planet(Virtual_planet&);							//Copy
	~Virtual_planet() {};

  void run();
	Faction& get_faction() { return Faction(world_, "neutre"); }		//Créé une faction neutre ?

protected:

	World & world_;
	unsigned pos_x_;	//position in the grid
	unsigned pos_y_;

  double production_rate_;	// 0 to 20
  double natural_defense_;	// 0 to 20

};

#endif
