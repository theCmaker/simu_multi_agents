#ifndef __FACTION_H__
#define __FACTION_H__

#include <string>
#include <list>

class World;
class Mother_land;
class Colonized_planet;

class Faction
{
private:
	World& world_;

	std::string									name_;
	double											money_;
	Mother_land								*	motherland_;
	std::list<Colonized_planet> colonies_;

	//private methods
	void loose();

public:
	
	Faction(World& world, std::string name = "default", Mother_land* = nullptr );	//Create a faction and convert a free planete into a mother land
	~Faction() {}

	void run() {}
	void init();


	Faction& operator= (Faction&) {return *this;}
	bool operator== (Faction &other) {return this->name_ == other.name_;}

	/*Faction& operator= (Faction) {
		return *this;
	}*/

	//Getter setter
	std::string get_name() {return name_;}
	double get_money() {return money_;}
	void add_to_banque(double adding_money) {money_ += adding_money;}
	Mother_land* get_motherland_() {return motherland_;}
	std::list<Colonized_planet> & get_colonies() {return colonies_;}
	void add_colony(Colonized_planet& colony) {colonies_.push_back(colony);}
};

#endif