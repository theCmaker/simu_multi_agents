#ifndef __MOTHER_LAND_H__
#define __MOTHER_LAND_H__

#include "Colonized_planet.hpp"

class Mother_land : public Colonized_planet
{
public:
  Mother_land(Virtual_planet* ,Faction&);
	~Mother_land() {};

  char display() { return faction_.get_motherland_symbol(); }
	bool is_attacked(Virtual_planet *);
};

#endif
