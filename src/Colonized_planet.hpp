#ifndef __COLONIZED_PLANET_H__
#define __COLONIZED_PLANET_H__

#include "Free_planet.hpp"

class Colonized_planet : public Virtual_planet
{
public:
  Colonized_planet();
  Colonized_planet(Free_planet *);
  ~Colonized_planet();

  bool attack(Free_planet *); //Bool: success
  bool attack(Colonized_planet *);

	Free_planet* convert_to_free_planet();

private:
  double colony_defense_;
  double colony_production_;
};

#endif /* end of include guard: __COLONIZED_PLANET_H__ */
