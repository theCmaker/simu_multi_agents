#include "Virtual_planet.hpp"
#include "Mother_land.hpp"
#include "World.hpp"
#include "Faction.hpp"



Faction::Faction(World& world, std::string name, Mother_land* mother_land) :
	world_(world),
	name_(name),
	money_(500),
	motherland_(mother_land)
{
}

void Faction::init() {
	unsigned x = World::gen_mt() % world_.len();
	unsigned y = World::gen_mt() % world_.hei();
	motherland_ = new Mother_land(world_.get_grid(x, y), *this);

	world_.set_grid(motherland_, x, y);
}

void Faction::run() {
	if (motherland_ == nullptr) {
		//Loose
		world_.kill_faction(*this);
	}
	else {
		//Give money to colonies
		for (list<pair<Colonized_planet*,double> >::iterator itr = demands_.begin(); itr != demands_.end();itr++) {
			if (money_ - itr->second >= 0) {
				money_ -= itr->second;
				itr->first->add_to_budget(itr->second);
			}
		}
	}
}

void Faction::remove_colony(Colonized_planet* colony) {
	std::list<Colonized_planet*>::iterator itr = std::find(colonies_.begin(), colonies_.end(), colony);
	colonies_.erase(itr);
}

void Faction::add_demand(Colonized_planet* demander, double cost) {
	demands_.push_back(std::pair< Colonized_planet*, double>(demander, cost));
}