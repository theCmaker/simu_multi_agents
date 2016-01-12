#ifndef __COLONIZED_PLANET_H__
#define __COLONIZED_PLANET_H__

#include "Free_planet.hpp"

class Colonized_planet : public Virtual_planet
{
public:
  
  //Colonized_planet(const Colonized_planet &);
  Colonized_planet(World &, unsigned, unsigned, Faction&);
  Colonized_planet(Free_planet *, Faction&);							//Transfome une free en colonise
	~Colonized_planet() {};

  bool attack(Free_planet *); //Bool: success
  bool attack(Colonized_planet *);

	//Free_planet* convert_to_free_planet();

	Faction& get_faction();

	void run();

  bool is_attacked(Virtual_planet *);

private:
  double colony_defense_;
  double colony_production_;
	Faction& faction_;
};

#endif
