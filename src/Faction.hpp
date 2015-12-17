#ifndef __FACTION_H__
#define __FACTION_H__

#include "Mother_land.hpp"

class Faction
{
public:
  Faction(World&, std::string name="defaut");	//Create a faction and convert a free planete into a mother land
  ~Faction();

  void run();

private:
	World& world_;

	std::string		name_;
  double				money_;
	Mother_land		*motherland_;
	std::list<Colonized_planet> colonies_;

	//private methods
  void loose();
};

#endif /* end of include guard: __FACTION_H__ */
