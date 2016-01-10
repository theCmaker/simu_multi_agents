#include "Colonized_planet.hpp"

Colonized_planet::Colonized_planet(World& world, unsigned pos_x, unsigned pos_y, Faction& fac) :
	Virtual_planet(world, pos_x, pos_y), faction_(fac) {}

Colonized_planet::Colonized_planet(Free_planet * fp, Faction& faction) :
	Virtual_planet(fp->world(), fp->pos_x(), fp->pos_y()),
	colony_defense_(),
	colony_production_(),
	faction_(faction){}

Colonized_planet::Colonized_planet(const Colonized_planet &other) : 
	Virtual_planet(other),
	colony_defense_(other.colony_defense_),
	colony_production_(other.colony_production_),
	faction_(other.faction_) {}

bool Colonized_planet::attack(Free_planet *) {
	/*A FAIRE !*/
	return true;
}
bool Colonized_planet::attack(Colonized_planet *) {
	/*A FAIRE !*/
	return true;
}

Faction& Colonized_planet::get_faction() {
	return faction_;
}