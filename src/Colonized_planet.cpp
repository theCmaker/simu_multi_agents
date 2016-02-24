#include "Colonized_planet.hpp"
#include "World.hpp"

Colonized_planet::Colonized_planet(World& world, unsigned pos_x, unsigned pos_y, Faction& fac) :
    Virtual_planet(world, pos_x, pos_y),
    colony_defense_(0),
    colony_production_(0),
    faction_(fac),
    target_(nullptr),
    budget_(0),demand_(0)
{
	//On ajoute colonized planet au waiting agent et a la liste de colonies de la faction
	world_.add_waiting_agent(this);
	faction_.add_colony(this);
}

Colonized_planet::Colonized_planet(Virtual_planet * fp, Faction& faction) :
	Virtual_planet(fp),
	colony_defense_(0),
	colony_production_(0),
	faction_(faction),
    target_(nullptr),
    budget_(0),demand_(0)
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
	
	bool res = victim->is_attacked(this);
    Colonized_planet * acquisition = nullptr;

	if (res) {
        acquisition = new Colonized_planet(victim,this->get_faction());
		for (unsigned i=0;i<victim->get_neighbourhood().size();i++){
			victim->get_neighbourhood()[i]->update_neighbourhood(victim,acquisition);
		}
		this->get_world().set_grid(acquisition, victim->pos_x(), victim->pos_y());
		delete victim;
	}
    return res;
}

bool Colonized_planet::is_attacked(Virtual_planet *attacker) {
	bool res = true;
	if (attacker->get_faction() == this->get_faction()) {
		res = false;
	}

    if (colony_defense_ > world_.gen_mt(0,99)){ //plus la defense est grande, plus les chances de conquete sont reduite (defense <=50)
        res = false;
        colony_defense_ -= world_.gen_mt(1,25); //la defense et l'eco baisse a cause de l'assaut
        colony_production_ -= world_.gen_mt(1,25);
        change();
    }
	//On supprime l'agent de la liste d'attente puiqu'il va etre elimine ainsi que de sa faction
	if (res == true) {
		world_.remove_waiting_agent(this);
		faction_.remove_colony(this);
	}
	return res;
}

//Transforme la colonie courante en free planete (!! ne supprime pas la colonie et ne met pas a jour le voisinage !!)
void Colonized_planet::convert_to_free_planet() {
	Free_planet * new_free_planet = new Free_planet(this);
	world_.set_grid(new_free_planet, new_free_planet->pos_x(), new_free_planet->pos_y());
}

void Colonized_planet::demand_to_faction(double cost) {
	faction_.add_demand(this, cost);
}

double Colonized_planet::estimate_cost() {
    return get_defense() * 10;
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

double Colonized_planet::get_production(){
    return production_rate_ + colony_production_;
}

void Colonized_planet::reinitialisate_target() {
	target_ = nullptr;
}


bool Colonized_planet::run() {
	bool found_victim,had_killed=false;
	unsigned i;

    int random_number = World::gen_mt(0, 1);

  switch (random_number){
		case 0:
			//Production, industry specialisation
            faction_.add_to_banque(production_rate_ + colony_production_);
            int inc;
            if (colony_production_ <= 20) {
                inc=World::gen_mt(0, 5);
                colony_production_ += inc;
                if(inc!=0) change();
			}
			
			if (colony_defense_ <= 50) {
                inc=World::gen_mt(0, 5);
				colony_defense_ += World::gen_mt(0, 5);
                if(inc!=0) change();
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
                    demand_ = target_->estimate_cost() - budget_;

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
                //Cas ou il n'y a pas d'attaque, la colonie produit alors
                faction_.add_to_banque(production_rate_ + colony_production_);
			}
			else {
				//attack
				if (budget_ >= target_->get_defense()) {
					budget_ -= target_->get_defense();
                    if(this->attack(target_)){
                        faction_.inc_nb_successful_attack_();
                    }else{
                        faction_.inc_nb_failed_attack_();
                    }
				}
				target_ = nullptr;
			}
			break;
		default:
			throw std::exception(/*"Bad random number"*/);
			break;
  }	
 // faction_.add_to_banque(production_rate_ + colony_production_);
  return had_killed;
//	colony_defense_ = (double)((int)(colony_defense_ + 1.0));
	//World::gen_mt()
}
