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

Faction::~Faction() {}

void Faction::kill(Faction & new_owner) {
	std::cout << "Faction " << name_ << " is about to be deleted." << std::endl;
	std::vector<Virtual_planet*> new_free_planets = std::vector<Virtual_planet*>();

	new_free_planets.push_back(new Colonized_planet(motherland_,new_owner));

	for (unsigned i = 0; i < new_free_planets.back()->get_neighbourhood().size(); ++i) {
		std::cout << *(new_free_planets.back()->get_neighbourhood()[i]) << std::endl;
	}

	world_.set_grid(new_free_planets.back(),motherland_->pos_x(),motherland_->pos_y());
	std::list<Colonized_planet*>::iterator i = colonies_.begin();

	while(i != colonies_.end()) {
		//mise à jour des voisins
		std::cout << "Old planet: " << **i << " going to be replaced." << std::endl;
		new_free_planets.push_back(new Free_planet(*i));
		Virtual_planet * vp = new_free_planets.back();
		std::cout << "New planet: " << *vp << " has been created." << std::endl;
		world_.set_grid(vp,(*i)->pos_x(),(*i)->pos_y());
		i++;
	}

	std::cout << "" << std::endl << std::endl;
	std::vector<Virtual_planet *>::iterator j = new_free_planets.begin();
	while (j != new_free_planets.end()) {
		for (unsigned i = 0; i < (*j)->get_neighbourhood().size(); ++i) {
			std::cout << "Mise a jour des voisins sur " << *((*j)->get_neighbourhood()[i]) << std::endl;
			(*j)->get_neighbourhood()[i]->set_neighbourhood();
		}
		++j;
	}
	i = colonies_.begin();
	while(i != colonies_.end()) {
		//suppression dans l'ordonnanceur
		world_.remove_waiting_agent(*i);
		//suppression des colonies
		remove_colony(*i);
		i = colonies_.begin();
	}
	world_.remove_waiting_agent(motherland_);
	std::cout << name_ << std::endl;
	world_.display();
}
/*
Faction & Faction::operator= (Faction & f) {
	world_ = f.world_;
	name_ = f.name_;
	money_ = f.money_;
	motherland_ = f.motherland_;
	return *this;
}
*/

void Faction::init() {
	unsigned x = World::gen_mt() % world_.len();
	unsigned y = World::gen_mt() % world_.hei();
	motherland_ = new Mother_land(world_.get_grid(x, y), *this);

	world_.set_grid(motherland_, x, y);
}

void Faction::run() {
	if (motherland_ == nullptr) {
		//Loose
		throw new std::exception();
	} else {
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
	if (itr != colonies_.end()) {
		colonies_.erase(itr);
	}
}

void Faction::add_demand(Colonized_planet* demander, double cost) {
	demands_.push_back(std::pair< Colonized_planet*, double>(demander, cost));
}
