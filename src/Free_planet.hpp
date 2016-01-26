#ifndef __FREE_PLANET_H__
#define __FREE_PLANET_H__

#include "Virtual_planet.hpp"

class Mother_land;
class Colonized_planet;

class Free_planet : public Virtual_planet
{
public:
  Free_planet(World &, unsigned, unsigned);
	~Free_planet() {};


	Mother_land* convert_to_mother_land();
	Colonized_planet* convert_to_colony();

	void run();
	bool is_attacked(Virtual_planet *);

private:
  
};

#endif
