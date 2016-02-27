#include "Free_planet.hpp"
#include "World.hpp"

/*!
 * \brief Constructeur
 * \param world Monde auquel est rattachée la planète
 * \param pos_x Ligne sur la grille
 * \param pos_y Colonne sur la grille
 */
Free_planet::Free_planet(World& world, unsigned pos_x, unsigned pos_y) :Virtual_planet(world, pos_x, pos_y) {}

/*!
 * \brief Crée une planète libre à partir d'une colonie
 * @see Colonized_planet
 * \param other planète servant de base
 *
 * \note Met à jour le voisinage en remplaçant l'ancienne par la nouvelle planète.
 */
Free_planet::Free_planet(Colonized_planet *other) : 
	Virtual_planet(other->get_world(), other->pos_x(), other->pos_y()) 
{
	for (unsigned i = 0 ; i < other->get_neighbourhood().size() ; i++) {
		other->get_neighbourhood()[i]->update_neighbourhood(other, this);
	}
}

/*!
 * \brief Joue le tour
 * \warning Ne doit jamais être appelée car une planète libre n'est pas sensée jouer.
 */
void Free_planet::run() {
}

/*!
 * \brief Répond à une attaque
 * \return Booléen à vrai 4 fois sur 5 en moyenne
 */
bool Free_planet::is_attacked(Virtual_planet *) {
    bool res = true;
    if(world_.gen_mt(0,4)==0){ //Une chance sur 5 de ne pas réussir
        res=false;
    }
    return res;
}
