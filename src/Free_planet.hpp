#ifndef __FREE_PLANET_H__
#define __FREE_PLANET_H__

#include "Virtual_planet.hpp"
#include "Colonized_planet.hpp"

class Free_planet : public Virtual_planet
{
public:
  Free_planet();
  Free_planet(Colonized_planet *);
  ~Free_planet();

private:
  std::list<Virtual_planet &> neighbourhood_;
};

#endif /* end of include guard: __FREE_PLANET_H__ */
