#include "Colonized_planet.hpp"
#include "World.hpp"

Colonized_planet::Colonized_planet(World& world, unsigned pos_x, unsigned pos_y, Faction& fac) :
	Virtual_planet(world, pos_x, pos_y), faction_(fac) {
	//On ajoute colonized planet au waiting agent
	world_.add_waiting_agent(this);
}

Colonized_planet::Colonized_planet(Free_planet * fp, Faction& faction) :
	Virtual_planet((Virtual_planet) *fp),
	colony_defense_(0),
	colony_production_(0),
	faction_(faction)
	{
		//On ajoute colonized planet au waiting agent
		world_.add_waiting_agent(this);
}

bool Colonized_planet::attack(Free_planet *victim) {
	bool res = victim->is_attacked(this);
	if (res) {
		Colonized_planet * acquisition = new Colonized_planet(victim,this->get_faction());
		this->world().set_grid(acquisition,
														victim->pos_x(),
														victim->pos_y());
		for (std::vector<Virtual_planet *>::iterator i = victim->neighbourhood().begin(); i != victim->neighbourhood().end(); ++i)
		{
			(*i)->update_neighbourhood(victim,acquisition);
		}
		delete victim;
	}
	return res;
}
bool Colonized_planet::attack(Colonized_planet *) {
	/*A FAIRE !*/
	return true;
}
bool Colonized_planet::is_attacked(Virtual_planet *attacker) {
	bool res = true;
	if (attacker->get_faction() == this->get_faction()) {
		res = false;
	} //TODO: Tenir compte des params de défense.
	return res;
}

Faction& Colonized_planet::get_faction() {
	return faction_;
}

void Colonized_planet::run() {
	faction_.add_to_banque(production_rate_ + colony_production_);
//	colony_defense_ = (double)((int)(colony_defense_ + 1.0));
	//world_.gen_mt()
}