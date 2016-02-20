#include "Mother_land.hpp"

Mother_land::Mother_land(Virtual_planet* fp, Faction& fac) : Colonized_planet(fp, fac) {}

bool Mother_land::is_attacked(Virtual_planet *attacker) {
	bool res = true;
	if (attacker->get_faction() == this->get_faction()) {
		res = false;
	}
	//On supprime l'agent de la liste d'attente puiqu'il va etre elimine ainsi que de sa faction
	if (res == true) {
		world_.remove_waiting_agent(this);
		faction_.remove_mother_land();
	}
	return res;
}


