#include "Colonized_planet.hpp"
#include "World.hpp"

Colonized_planet::Colonized_planet(World& world, unsigned pos_x, unsigned pos_y, Faction& fac) :
	Virtual_planet(world, pos_x, pos_y), faction_(fac), target_(nullptr){
	//On ajoute colonized planet au waiting agent et a la liste de colonies de la faction
	world_.add_waiting_agent(this);
	faction_.add_colony(this);
}

Colonized_planet::Colonized_planet(Virtual_planet * fp, Faction& faction) :
	Virtual_planet(fp),
	colony_defense_(0),
	colony_production_(0),
	faction_(faction),
	target_(nullptr)
	//TODO: refaire ce constructeur avec recopie des valeurs de colonized planet
	{
		//On initialise le voisinage
		for (unsigned i = 0;i<fp->get_neighbourhood().size();i++) {
			fp->get_neighbourhood()[i]->update_neighbourhood(fp, this);
		}

		//On ajoute colonized planet au waiting agent et a la liste de colonies de la faction
		world_.add_waiting_agent(this);
		faction_.add_colony(this);
}

void Colonized_planet::update_neighbourhood(Virtual_planet *old_one, Virtual_planet *new_one) {
	Virtual_planet::update_neighbourhood(old_one, new_one);
	// if the target is compromised
	if (old_one == target_) {
		target_ = nullptr;		//reinitialisation
	}
}

bool Colonized_planet::attack(Virtual_planet *victim) {
	
	//cout << victim->neighbourhood()[0]->neighbourhood().front()->pos_x() << endl;
	bool res = victim->is_attacked(this);

	if (res) {
		Colonized_planet * acquisition = new Colonized_planet(victim,this->get_faction());
	/*	for (unsigned i=0;i<victim->get_neighbourhood().size();i++){
			victim->get_neighbourhood()[i]->update_neighbourhood(victim,acquisition);
		}*/
		this->world().set_grid(acquisition, victim->pos_x(), victim->pos_y());
		delete victim;
	}
	return true;
}

/*
bool Colonized_planet::attack(Colonized_planet *) {
	return true;
}
*/

bool Colonized_planet::is_attacked(Virtual_planet *attacker) {
	bool res = true;
	if (attacker->get_faction() == this->get_faction()) {
		res = false;
	}
	//On supprime l'agent de la liste d'attente puiqu'il va etre elimine ainsi que de sa faction
	if (res = true) {
		world_.remove_waiting_agent(this);
		faction_.remove_colony(this);
	}
	return res;
}

void Colonized_planet::demand_to_faction(double cost) {
	faction_.add_demand(this, cost);
}

double Colonized_planet::estimate_cost(Virtual_planet* target) {
	return target->get_defense();
}

void Colonized_planet::add_to_budget(double given_money) {
	budget_ += given_money;
	demand_ -= given_money;
}


Faction& Colonized_planet::get_faction() {
	return faction_;
}

double Colonized_planet::get_defense() {
	return natural_defense_ + colony_defense_;
}

void Colonized_planet::reinitialisate_target() {
	target_ = nullptr;
}


void Colonized_planet::run() {
	bool found_victim;
	unsigned i;

	int random_number = World::gen_mt(0, 1);;

  switch (random_number){
		case 0:
			//Production, industry specialisation
  		//TODO: croissance logarithmique du taux de prod
			if (colony_production_ <= 50) {
				colony_production_ += World::gen_mt(0, 5);
			}
			
			if (colony_defense_ <= 50) {
				colony_defense_ += World::gen_mt(0, 5);
			}
			break;

		case 1:
			//choose the war way
			if (target_ == nullptr) {
				//select a target and estimate cost
				//selection
				random_shuffle(neighbourhood_.begin(), neighbourhood_.end(),World::gen_mt_shuffle);
				i = 0;
				found_victim = false;
				while (i < neighbourhood_.size() && !found_victim) {
					Faction fac = this->neighbourhood_[i]->get_faction();
					if (!(neighbourhood_[i]->get_faction() == this->get_faction())) {
						found_victim = true;
					}
					else {
						++i;
					}
				}

				if (found_victim) {
					// demand of subvention
					target_ = neighbourhood_[i];
					demand_ = estimate_cost(target_) - budget_;

					if (demand_ > 0) {
						faction_.add_demand(this, demand_);
					}
					else {
						demand_ = 0;
					}
				}
				else {
					//aborted
					target_ = nullptr;
				}				
			}
			else {
				//attack
				if (budget_ >= target_->get_defense()) {
					budget_ -= target_->get_defense();
					attack(target_);
				}
				target_ = nullptr;
			}
			break;
		default:
			throw exception("Bad random number");
			break;
  }	
  faction_.add_to_banque(production_rate_ + colony_production_);
  
//	colony_defense_ = (double)((int)(colony_defense_ + 1.0));
	//World::gen_mt()
}
