#include "Neutral_faction.hpp"
#include <iostream>

/*!
 * \brief Constructeur
 * \param world Monde auquel appartient la faction neutre
 */
Neutral_faction::Neutral_faction(World& world):
	Faction(world,"Neutral")
{
    instance_ = this;
}

/*!
 * \brief Demande de la planète neutre
 * \param world Monde auquel la faction neutre appartient
 * \return pointeur sur l'instance unique de la faction neutre
 */
Neutral_faction * Neutral_faction::get_instance(World& world) {
    if (instance_ == nullptr) {
        instance_ = new Neutral_faction(world);
    }
    return instance_;
}

/*!
 * \brief Libère l'instance
 */
void Neutral_faction::dispose() {
	delete instance_;
	instance_ = nullptr;
}


//Initialization
Neutral_faction* Neutral_faction::instance_ = nullptr;
