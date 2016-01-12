#ifndef __FACTION_H__
#define __FACTION_H__

#include <string>
#include <list>

class World;
class Mother_land;
class Colonized_planet;

class Faction
{
public:
	Faction(World& world, std::string name = "defaut");	//Create a faction and convert a free planete into a mother land
	~Faction() {}

	void run() {}

	std::string get_name();

	Faction& operator= (Faction&) {
		return *this;
	}

	Faction& operator= (Faction) {
		return *this;
	}

	void add_to_banque(double adding_money) {
		money_ += adding_money;
	}

	bool operator== (Faction &other) {
		return this->name_ == other.name_;
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