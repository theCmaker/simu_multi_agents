#ifndef __MOTHER_LAND_H__
#define __MOTHER_LAND_H__

#include "Colonized_planet.hpp"

class Mother_land : public Colonized_planet
{
public:
  Mother_land(Free_planet *,Faction&);
	~Mother_land() {};
};

#endif
