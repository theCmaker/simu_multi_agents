#include "Colonized_planet.hpp"
#include "World.hpp"

/*!
 * \brief Constructeur, prépare la planète
 *
 * Met à jour la liste des agents en attente et ajoute la planète à la liste des colonies de la faction.
 *
 * \param world plateau de jeu
 * \param pos_x numéro de la ligne sur la grille
 * \param pos_y numéro de la colonne sur la grille
 * \param fac   faction à laquelle doit appartenir la nouvelle planète
 */
Colonized_planet::Colonized_planet(World& world, unsigned pos_x, unsigned pos_y, Faction& fac) :
  Virtual_planet(world, pos_x, pos_y),
  colony_defense_(0.),
  colony_production_(0.),
  faction_(fac),
  target_(nullptr),
  budget_(0.),
  demand_(0.)
{
	//On ajoute colonized planet au waiting agent et a la liste de colonies de la faction
	world_.add_waiting_agent(this);
	faction_.add_colony(this);
}

/*!
 * \brief Création d'une planète colonisée à partir d'une autre planète
 *
 * \param fp       planète d'origine
 * \param faction  faction à laquelle doit appartenir la nouvelle planète
 *
 * \note Tient compte du voisinage de l'ancienne planète et le met à jour
 */
Colonized_planet::Colonized_planet(Virtual_planet * fp, Faction& faction) :
Virtual_planet(fp),
colony_defense_(0.),
colony_production_(0.),
faction_(faction),
target_(nullptr),
budget_(0.),
demand_(0.)
{
	//On initialise le voisinage
	for (unsigned i = 0;i<fp->get_neighbourhood().size();i++) {
		fp->get_neighbourhood()[i]->update_neighbourhood(fp, this);
	}

	//On ajoute colonized planet au waiting agent et a la liste de colonies de la faction
	world_.add_waiting_agent(this);
	faction_.add_colony(this);
}

const int Colonized_planet::MAX_COLONY_DEFENSE = 50;
const int Colonized_planet::MAX_COLONY_PRODUCTION = 15;
const int Colonized_planet::COLONY_MULTIPLICATOR = 10;

/*!
 * \brief Mise à jour du voisinage
 *
 * Parcourt le voisinage de la planète courante et remplace old_one par new_one dans la liste.
 *
 * \param old_one ancienne planète
 * \param new_one nouvelle planète
 *
 * \note Si l'ancienne planète était la cible de l'un des voisins, alors cette cible est effacée.
 */
void Colonized_planet::update_neighbourhood(Virtual_planet *old_one, Virtual_planet *new_one) {
	Virtual_planet::update_neighbourhood(old_one, new_one);
	// if the target is compromised
	if (old_one == target_) {
        reinitialisate_target();		//reinitialisation
	}
}

/*!
 * \brief Attaque une planète
 * \param victim planète qui est attaquée
 * \return victoire de l'attaque
 */
bool Colonized_planet::attack(Virtual_planet *victim) {
	bool res = victim->is_attacked(this);
    Colonized_planet * acquisition = nullptr;

	if (res) {
        acquisition = new Colonized_planet(victim,this->get_faction());
        for (unsigned i = 0 ; i<victim->get_neighbourhood().size() ; i++){
			victim->get_neighbourhood()[i]->update_neighbourhood(victim,acquisition);
		}
		this->get_world().set_grid(acquisition, victim->pos_x(), victim->pos_y());
		delete victim;
		victim = nullptr;
	}
    return res;
}

/*!
 * \brief La planète est attaquée
 *
 * Lorsque la planète est attaquée, elle tente de parer l'attaque.
 * Son score de défense est utilisé et peut être inpacté ainsi que la valeur de production.
 *
 * \param attacker planète offensive
 * \return victoire de l'attaque
 *
 * \note Si la planète ne parvient pas à parer l'attaque alors elle est éliminée de la liste d'attente de jeu car elle sera supprimée par la suite.
 *
 * @see colony_production_
 * @see colony_defense_
 */
bool Colonized_planet::is_attacked(Virtual_planet *attacker) {
	bool res = true;
	if (attacker->get_faction() == this->get_faction()) {
		res = false;
	}

    if (colony_defense_ > world_.gen_mt(0,99)){ //plus la defense est grande, plus les chances de conquete sont réduites (defense <= 50)
        res = false;
        colony_defense_ -= world_.gen_mt(1,25); //la defense et l'eco baisse a cause de l'assaut
        colony_production_ -= world_.gen_mt(1,25);
        change();
    }
	//On supprime l'agent de la liste d'attente puiqu'il va etre elimine ainsi que de sa faction
	if (res == true) {
		world_.remove_waiting_agent(this);
		faction_.remove_colony(this);
		faction_.remove_demand(this);
	}
	return res;
}

/*!
 * \brief Transforme la colonie courante en free planete
 * \warning Ne supprime pas la colonie et ne met pas a jour le voisinage !!
 */
void Colonized_planet::convert_to_free_planet() {
	Free_planet * new_free_planet = new Free_planet(this);
	world_.set_grid(new_free_planet, new_free_planet->pos_x(), new_free_planet->pos_y());
}

/*!
 * \brief Réalise une demande de fonds auprès de la faction
 * \param cost Montant demandé
 */
void Colonized_planet::demand_to_faction(double cost) {
	faction_.add_demand(this, cost);
}

/*!
 * \brief Estime le coût d'une attaque
 * \return coût estimé
 */
double Colonized_planet::estimate_cost() {
  return get_defense() * COLONY_MULTIPLICATOR;
}

/*!
 * \brief Ajoute les fonds obtenus auprès de la faction
 *
 * Augmente le budget du montant obtenu, et diminue d'autant la demande précédemment effectuée.
 *
 * \param given_money Montant obtenu
 */
void Colonized_planet::add_to_budget(double given_money) {
	budget_ += given_money;
	demand_ -= given_money;
}

/*!
 * \brief Faction à laquelle appartient la planète
 * \return faction
 */
Faction& Colonized_planet::get_faction() {
	return faction_;
}

/*!
 * \brief Défense totale de la planète
 * \return somme de la défense naturelle de la planète et de celle de la colonie
 */
double Colonized_planet::get_defense() {
	return natural_defense_ + colony_defense_;
}

/*!
 * \brief Production de la planète
 * \return somme de la production naturelle de la planète et de celle de la colonie
 */
double Colonized_planet::get_production(){
  return production_rate_ + colony_production_;
}

/*!
 * \brief Réinitialise la cible, annule la tentative d'attaque
 */
void Colonized_planet::reinitialisate_target() {
	target_ = nullptr;
}

/*!
 * \brief Joue le tour
 *
 * La planète peut choisir d'attaquer ou bien de produire des richesses.
 *
 * \return Booléen indiquant si la planète a réalisé une attaque
 * \todo à quoi sert had_killed?
 */
bool Colonized_planet::run() {
	bool found_victim,had_killed=false;
	unsigned i;

    int random_number = World::gen_mt(0, 1);

    switch (random_number){
		case 0:
			//Production, industry specialisation
            faction_.add_to_banque(production_rate_ + colony_production_);
            int inc;
            if (colony_production_ <= MAX_COLONY_PRODUCTION) {
                inc = World::gen_mt(0, 5);
                colony_production_ += inc;
                if (inc != 0) change();
            }

            if (colony_defense_ <= MAX_COLONY_DEFENSE) {
                inc = World::gen_mt(0, 5);
				colony_defense_ += World::gen_mt(0, 5);
                //TODO
                //!\todo pourquoi pas += inc ici ?
                if (inc != 0) change();
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
                    } else {
						++i;
					}
				}

				if (found_victim) {
					// demand of subvention
					target_ = neighbourhood_[i];
                    demand_ = target_->estimate_cost() - budget_;

					if (demand_ > 0) {
						faction_.add_demand(this, demand_);
                    } else {
						demand_ = 0;
					}
                } else {
					//aborted
					target_ = nullptr;
                }
                //Cas ou il n'y a pas d'attaque, la colonie produit alors
                faction_.add_to_banque(production_rate_ + colony_production_);
			} else {
				//attack
				if (budget_ >= target_->get_defense()) {
					budget_ -= target_->get_defense();
                    if(this->attack(target_)){
                        faction_.inc_nb_successful_attack_();
                    } else {
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
