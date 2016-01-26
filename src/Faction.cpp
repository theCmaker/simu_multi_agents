#include "Virtual_planet.hpp"
#include "Mother_land.hpp"
#include "World.hpp"
#include "Faction.hpp"



Faction::Faction(World& world, std::string name, Mother_land* mother_land) :
	world_(world),
	name_(name),
	money_(0),
	motherland_(mother_land),
	colonies_(std::list<Colonized_planet>())
{
}

void Faction::init() {
	unsigned x = world_.gen_mt() % world_.len();
	unsigned y = world_.gen_mt() % world_.hei();
	motherland_ = new Mother_land(*world_.get_grid(x, y), *this);

	world_.set_grid(motherland_, x, y);
}
