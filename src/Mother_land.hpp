#ifndef __MOTHER_LAND_H__
#define __MOTHER_LAND_H__

#include "Colonized_planet.hpp"

class Mother_land : public Colonized_planet
{
public:
  Mother_land();
  Mother_land(Free_planet *);
  ~Mother_land();

private:
};

#endif /* end of include guard: __MOTHER_LAND_H__ */
