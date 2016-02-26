#ifndef __MOTHER_LAND_H__
#define __MOTHER_LAND_H__

#include "Colonized_planet.hpp"
#include "World.hpp"

class Mother_land : public Colonized_planet
{
public:
  Mother_land(Virtual_planet* ,Faction&);
	~Mother_land() {};

  char display() { return faction_.get_motherland_symbol(); }
  std::string get_color_name() { return faction_.get_motherland_color_name();}
	bool is_attacked(Virtual_planet *);
};

#endif
