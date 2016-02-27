#include "Virtual_planet.hpp"
#include "Mother_land.hpp"
#include "World.hpp"
#include "Faction.hpp"

/*!
 * \brief Constructeur
 * \param world Monde auquel appartient la faction
 * \param name Nom de la faction
 * \param mother_land Planète mère de la faction
 */
Faction::Faction(World& world, std::string name, Mother_land* mother_land) :
	world_(world),
	name_(name),
    money_(0.),
    motherland_(mother_land),
    motherland_symbol_('N'),
    colony_symbol_('n'),
    colony_color_name_("gray"),
    motherland_color_name_("darkGray"),

    //stats
    money_spent_(0.),
    money_produce_(0.),
    nb_successful_attack_(0),
    nb_failed_attack_(0)
{
}

/*!
 * \brief Supprime une colonie
 * \param colony colonie à supprimer
 */
void Faction::remove_colony(Colonized_planet* colony) {
	std::list<Colonized_planet*>::iterator itr = std::find(colonies_.begin(), colonies_.end(), colony);
	if (itr != colonies_.end()) {
		colonies_.erase(itr);
	}
}

/*!
 * \brief Supprime la planète mère
 *
 * \note Cette méthode ne détruit pas la faction.
 */
void Faction::remove_mother_land(){
	std::list<Colonized_planet*>::iterator itr = std::find(colonies_.begin(), colonies_.end(), motherland_);
	if (itr != colonies_.end()) {
		colonies_.erase(itr);
	}
	motherland_ = nullptr;
}

/*!
 * \brief Supprime une demande de fonds
 * \param colony colonie qui a initié la demande
 */
void Faction::remove_demand(Colonized_planet* colony) {
	Comparator comp(colony);
	std::list<pair<Colonized_planet*, double> >::iterator itr = std::find_if(demands_.begin(), demands_.end(), comp);
	while (itr != demands_.end()) {
		demands_.erase(itr);
		itr = std::find_if(demands_.begin(), demands_.end(), comp);
	}
}

/*!
 * \brief Ajoute de l'argent généré à la banque
 * \param adding_money quantité d'argent à ajouter
 */
void Faction::add_to_banque(double adding_money) {
    money_ += adding_money;
    money_produce_ += adding_money;
}

/*!
 * \brief Tue la faction
 *
 * \warning Provoque la suppression définitive des colonies
 * \note Le voisinage et l'ordonnanceur sont mis à jour
 */
void Faction::die() {
	cout << "Faction " << name_ << " is about to be deleted." << endl;
	
	// conversion dans la grille de jeu
	for (list<Colonized_planet*>::iterator it = colonies_.begin() ; it != colonies_.end() ; it++) {
		(*it)->convert_to_free_planet();
	}

	// mise a jour du voisinage
	for (list<Colonized_planet*>::iterator it = colonies_.begin() ; it != colonies_.end() ; it++) {
		(*it)->set_neighbourhood(); //on va cherche les voisins sur la grille
		for (unsigned i = 0 ; i<(*it)->get_neighbourhood().size() ; i++) {
			(*it)->get_neighbourhood()[i]->set_neighbourhood();	//on met a jour les dits voisins
		}
	}

	// suppression des colonies
	list<Colonized_planet*>::iterator it = colonies_.begin();
	while (it != colonies_.end())
	{
		//suppression dans l'ordonnanceur
		world_.remove_waiting_agent(*it);
		
		//suppression des colonies
		delete *it;
		colonies_.erase(it++);
	}
}

/*!
 * \brief Initialise la faction
 *
 * \note Crée la planète mère n'importe où sur la grille
 *
 * \todo Vérifier si la place n'est pas déja occupée par une autre planète mère
 */
void Faction::init() {
	unsigned x = World::gen_mt() % world_.len();
	unsigned y = World::gen_mt() % world_.hei();
	motherland_ = new Mother_land(world_.get_grid(x, y), *this);
	delete world_.get_grid(x,y);
	world_.set_grid(motherland_, x, y);
}

/*!
 * \brief Lance le jeu
 *
 * Si la planète mère a été détruite, la faction est supprimée.
 *
 * @see die()
 * \return pointeur sur la faction qui a été détruite.
 * \note En cas de non-destruction de la faction, le pointeur est nul.
 */
Faction* Faction::run() {
	Faction * res = nullptr;
	if (motherland_ == nullptr) {
		//Loose
		die();
		res = this;
	} else {
		//Give money to colonies
		list<pair<Colonized_planet*,double> >::iterator itr = demands_.begin();
		while (itr != demands_.end()) {
      if (money_ - itr->second >= 0) {
        money_ -= itr->second;
        money_spent_ += itr->second;
				itr->first->add_to_budget(itr->second);
				itr = demands_.erase(itr);
			} else {
				itr++;
			}
		}
	}
	return res;
}

/*!
 * \brief Ajoute une demande de fonds à la liste des demandes
 * \param demander La planète effectuant la demande
 * \param cost Le montant demandé
 */
void Faction::add_demand(Colonized_planet* demander, double cost) {
	demands_.push_back(std::pair< Colonized_planet*, double>(demander, cost));
}

/*!
 * \brief Augmente le compteur d'attaques réussies
 */
void Faction::inc_nb_successful_attack_(){
    nb_successful_attack_++;
}

/*!
 * \brief Augmente le compteur d'attaques échouées
 */
void Faction::inc_nb_failed_attack_(){
    nb_failed_attack_++;
}

/*!
 * \brief Texte représentant une faction
 * \return bloc de texte reprenant les paramètres principaux et de statistiques
 */
string Faction::toString(){
    std::stringstream ss;
    ss << "Name : " << get_name() << endl;
    ss << "Money : " << get_money() << endl;
    ss << "Money produced : " << get_money_produce_() << endl;
    ss << "Money spent : " << get_money_spent() << endl;
    ss << "Number of colonies : " << colonies_.size() << endl;
    ss << "Number of attacks : " << get_nb_failed_attack_() + get_nb_successful_attack_() << endl;
    ss << "Number of successful attacks : " << get_nb_successful_attack_() << endl;
    ss << "Number of failed attacks : " << get_nb_failed_attack_() << endl;
    ss << "----------------------------" << endl;
    return ss.str();
}
