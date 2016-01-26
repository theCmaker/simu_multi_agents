#include "Colonized_planet.hpp"
#include "World.hpp"

Colonized_planet::Colonized_planet(World& world, unsigned pos_x, unsigned pos_y, Faction& fac) :
	Virtual_planet(world, pos_x, pos_y), faction_(fac) {
	//On ajoute colonized planet au waiting agent
	world_.add_waiting_agent(this);
}

Colonized_planet::Colonized_planet(Virtual_planet * fp, Faction& faction) :
	Virtual_planet(fp),
	colony_defense_(0),
	colony_production_(0),
	faction_(faction)
	//TODO: refaire ce constructeur avec recopie des valeurs de colonized planet
	{
		//On initialise le voisinage
		for (unsigned i = 0;i<fp->get_neighbourhood().size();i++) {
			fp->get_neighbourhood()[i]->update_neighbourhood(fp, this);
		}
		//On ajoute colonized planet au waiting agent
		world_.add_waiting_agent(this);
}

bool Colonized_planet::attack(Virtual_planet *victim) {
	
	//cout << victim->neighbourhood()[0]->neighbourhood().front()->pos_x() << endl;
	bool res = victim->is_attacked(this);

	if (res) {
		Colonized_planet * acquisition = new Colonized_planet(victim,this->get_faction());
		for (unsigned i=0;i<victim->get_neighbourhood().size();i++){
			victim->get_neighbourhood()[i]->update_neighbourhood(victim,acquisition);
		}
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
	} else{
		
	}//TODO: Tenir compte des params de défense.

	//On supprime l'agent de la liste d'attente puiqu'il va etre elimine
	if (res = true) {
		world_.remove_waiting_agent(this);
	}
	return res;
}

Faction& Colonized_planet::get_faction() {
	return faction_;
}

void Colonized_planet::run() {
  if (world_.gen_mt(0,1)) { 
    //Production, specialisation d'industrie
  	//TODO: croissance logarithmique du taux de prod
  	colony_production_ += world_.gen_mt(0,5);
  } else {
    //Attaque
    //std::vector<Virtual_planet *>::iterator itr = this->neighbourhood().begin();
    unsigned i = 0;
    bool found_victim = false;
    while (i < neighbourhood_.size() && !found_victim) {
		Faction fac = this->neighbourhood_[i]->get_faction();
      if (!(neighbourhood_[i]->get_faction() == this->get_faction())) {
        found_victim = true;
      } else {
        ++i;
      }
    }
    if (found_victim) {
      attack(neighbourhood_[i]);
    }
  }	
  faction_.add_to_banque(production_rate_ + colony_production_);
  
//	colony_defense_ = (double)((int)(colony_defense_ + 1.0));
	//world_.gen_mt()
}
