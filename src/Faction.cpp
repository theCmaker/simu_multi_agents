#include "Faction.hpp"
#include "Virtual_planet.hpp"
#include "Mother_land.hpp"
#include "World.hpp"


Faction::Faction(World& world, std::string name):
world_(world), name_(name),money_(0)
{
	//colonies_ = new std::list<Colonized_planet>[1];
	//Find the mother_land
	unsigned x = world_.gen_mt() % world_.len();
	unsigned y = world_.gen_mt() % world_.hei();

	/*WARNING : WHAT HAPPENS IF THE PLANET ISNT FREE? */

	//Creation of motherland
	motherland_=new Mother_land((Free_planet*)world_.get_grid(x, y),*this);
	world_.set_grid(motherland_, x, y);
}

std::string Faction::get_name() {
	return name_;
}