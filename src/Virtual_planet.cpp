#include "Virtual_planet.hpp"
#include "World.hpp"

/*!
 * \brief Constructeur
 * \param world Monde auquel la planète appartient
 * \param pos_x Ligne dans la grille
 * \param pos_y Colonne dans la grille
 */
Virtual_planet::Virtual_planet(World& world, unsigned pos_x, unsigned pos_y):
	world_(world),
	pos_x_(pos_x),
    pos_y_(pos_y),
    changed_(true)
{
    production_rate_ = (double)(World::gen_mt(MIN_PRODUCTION_RATE,MAX_PRODUCTION_RATE));
    natural_defense_ = (double)(World::gen_mt(MIN_NATURAL_DEFENSE,MAX_NATURAL_DEFENSE));
}

/*!
 * \brief Constructeur par copie
 * \param other Planète d'origine
 */
Virtual_planet::Virtual_planet(Virtual_planet *other) :
	world_(other->world_),
	pos_x_(other->pos_x_),
	pos_y_(other->pos_y_),
	production_rate_(other->production_rate_),
	natural_defense_(other->natural_defense_)
	{
		for (unsigned i=0 ; i<other->neighbourhood_.size() ; i++){
			neighbourhood_.push_back(other->neighbourhood_[i]);
		}
}

const int Virtual_planet::MIN_PRODUCTION_RATE = 0;
const int Virtual_planet::MAX_PRODUCTION_RATE = 15;
const int Virtual_planet::MIN_NATURAL_DEFENSE = 25;
const int Virtual_planet::MAX_NATURAL_DEFENSE = 50;

/*!
 * \brief Calcule le voisinage de la planète
 * \note Grille torique
 */
void Virtual_planet::set_neighbourhood2() {
	for (int i = -1 ; i < 2 ; ++i) {
        for (int j = -1 ; j < 2 ; ++j) {
            if ( i != 0 || j != 0)
                neighbourhood_.push_back(world_.get_grid((((int)pos_x_) + i)%world_.len(), ((((int)pos_y_) + j)%world_.hei())));
        }
	}
}

/*!
 * \brief Calcule le voisinage de la planète
 */
void Virtual_planet::set_neighbourhood() {
	bool dosmth;
	neighbourhood_.clear();
	for (int i = -1 ; i<=1 ; i++) {
		for (int j = -1 ; j<=1 ; j++) {
			dosmth = true;
			if (((int)pos_x_) + i < 0 || ((int)pos_y_) + j < 0) {
				dosmth = false;
			}

			if (((int)pos_x_) + i >= (int)world_.len() || ((int)pos_y_) + j >= (int)world_.hei()) {
				dosmth = false;
			}

			if (i == 0 && j == 0) {
				dosmth = false;
			}
			if (dosmth) {
				neighbourhood_.push_back(world_.get_grid(((int)pos_x_) + i, ((int)pos_y_) + j));
			}
		}
	}
}

/*!
 * \brief Met à jour le voisinage
 * \param old_one planète à remplacer
 * \param new_one planète remplaçante
 */
void Virtual_planet::update_neighbourhood(Virtual_planet *old_one,Virtual_planet *new_one) {
	std::vector<Virtual_planet *>::iterator itr= std::find(neighbourhood_.begin(),neighbourhood_.end(),old_one);
	if (itr != neighbourhood_.end()) {
		*itr = new_one;
	}
}

/*!
 * \brief Joue sur le plateau
 * \note Non utilisée
 */
void Virtual_planet::run() {
	//Non utilisé
}

/*!
 * \brief Obtenir la faction à laquelle appartient la planète
 * \return Faction neutre par défaut
 */
Faction& Virtual_planet::get_faction() {
    Faction* test = Neutral_faction::get_instance(world_);
    return *test;
}

/*!
 * \brief Récupère un changement
 * \return l'état de changement
 *
 * \note réinitialise l'état de changement s'il était actif
 */
bool Virtual_planet::has_changed(){
    bool res = changed_;
    if (changed_)   changed_ = false;
    return res;
}

/*!
 * \brief Signale un changement d'état
 */
void Virtual_planet::change(){
    changed_=true;
}

/*!
 * \brief Affichage d'une planète
 * \param o flux dans lequel afficher
 * \param vp planète à afficher dans le flux
 * \return flux de destination pour chaînage
 *
 * \note Affichage peu utilisé, surtout pour la DEBUG
 */
std::ostream & operator<< (std::ostream &o, Virtual_planet &vp) {
	o << "Planet at (" << vp.pos_x() <<  ',' << vp.pos_y() << ") of faction " << vp.get_faction().get_name();
	return o;
}
