#include "Mother_land.hpp"

/*!
 * \brief Constructeur
 *
 * Appelle le constructeur de Colonized_planet
 *
 * @see Colonized_planet
 *
 * \param fp  Planète présente précédemment
 * \param fac Faction à laquelle est rattachée la planète mère
 */
Mother_land::Mother_land(Virtual_planet* fp, Faction& fac) : Colonized_planet(fp, fac) {}

/*!
 * \brief Répond à une attaque
 * \param attacker Planète attaquante
 * \return vrai si l'attaquant n'appartient pas à la même faction
 *
 * \note Tir ami interdit
 */
bool Mother_land::is_attacked(Virtual_planet *attacker) {
	bool res = true;
	if (attacker->get_faction() == this->get_faction()) {
		res = false;
	}
	//On supprime l'agent de la liste d'attente puiqu'il va etre elimine ainsi que de sa faction
	if (res == true) {
		world_.remove_waiting_agent(this);
		faction_.remove_mother_land();
		faction_.remove_demand(this);
	}
	return res;
}


