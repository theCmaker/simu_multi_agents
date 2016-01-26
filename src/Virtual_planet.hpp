#ifndef __VIRTUAL_PLANET_H__
#define __VIRTUAL_PLANET_H__

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <exception>
#include <algorithm>

#include "Faction.hpp"


class World;

class Virtual_planet
{
public:
	

  Virtual_planet(World&, unsigned, unsigned);		//Creation of random stat
  Virtual_planet(const Virtual_planet&);
	//Virtual_planet(const Virtual_planet&);				//Copy
	virtual ~Virtual_planet() {};

	void set_neighbourhood();	//generate neighbourhood
	void update_neighbourhood(Virtual_planet *,Virtual_planet *); //update changes to neighbourhood when planet is attacked.

  virtual char display() { return '.'; }
  void run();
	virtual Faction& get_faction() { return faction_neutre_;  }

	unsigned pos_x() { return pos_x_; }
	unsigned pos_y() { return pos_y_; }
	World& world() { return world_; }
	virtual bool is_attacked(Virtual_planet *) {return false; };
	
	/*virtual bool attack(Virtual_planet *) = 0; */
	
	std::vector<Virtual_planet* > neighbourhood() { return neighbourhood_ ; }

protected:

	World & world_;
	unsigned pos_x_;	//position in the grid
	unsigned pos_y_;

	std::vector<Virtual_planet* > neighbourhood_;

  double production_rate_;	// 0 to 20
  double natural_defense_;	// 0 to 20

private:
	//Faction neutre
	Faction faction_neutre_;
};

#endif
