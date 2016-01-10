#ifndef __FACTION_H__
#define __FACTION_H__

#include <string>
#include <list>

class Mother_land;
class Colonized_planet;
class World;

class Faction
{
public:
	Faction(World& world, std::string name = "defaut");	//Create a faction and convert a free planete into a mother land
	~Faction() {}

	void run() {}

	std::string get_name();

	Faction& operator= (Faction& fac) {
		return fac;
	}

private:
	World& world_;

	std::string									name_;
  double											money_;
	Mother_land									*motherland_;
	std::list<Colonized_planet> colonies_;

	//private methods
  void loose();
};

#endif