#include "Virtual_planet.hpp"
#include "Mother_land.hpp"
#include "World.hpp"
#include "Faction.hpp"

Faction::Faction(World& world, std::string name, Mother_land* mother_land) :
	world_(world),
	name_(name),
    money_(0),
    motherland_(mother_land),
    motherland_symbol_('N'),
    colony_symbol_('n'),
    colony_color_name_("gray"),
    motherland_color_name_("darkGray"),

    //stats
    money_spent_(0),
    money_produce_(0),
    nb_successful_attack_(0),
    nb_failed_attack_(0)
{
}

Faction::~Faction() {}

void Faction::remove_colony(Colonized_planet* colony) {
	std::list<Colonized_planet*>::iterator itr = std::find(colonies_.begin(), colonies_.end(), colony);
	if (itr != colonies_.end()) {
		colonies_.erase(itr);
	}
}

void Faction::remove_mother_land(){
	std::list<Colonized_planet*>::iterator itr = std::find(colonies_.begin(), colonies_.end(), motherland_);
	if (itr != colonies_.end()) {
		colonies_.erase(itr);
	}
	motherland_ = nullptr;
}

void Faction::add_to_banque(double adding_money) {
    money_ += adding_money;
    money_produce_ += adding_money;
}

void Faction::die() {
	cout << "Faction " << name_ << " is about to be deleted." << endl;
	
	// convertion dans la grille de jeu
	for (list<Colonized_planet*>::iterator it = colonies_.begin(); it != colonies_.end(); it++){
		(*it)->convert_to_free_planet();
	}

	// mise a jour du voisinage
	for (list<Colonized_planet*>::iterator it = colonies_.begin(); it != colonies_.end(); it++) {
		(*it)->set_neighbourhood(); //on va cherche les voisins sur la grille
		for (unsigned i = 0;i<(*it)->get_neighbourhood().size();i++) {
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
		colonies_.erase(it++);
	}
	std::cout << name_ << std::endl;
	world_.remove_faction(this);
	world_.display();
}

void Faction::init() {
	unsigned x = World::gen_mt() % world_.len();
	unsigned y = World::gen_mt() % world_.hei();
	motherland_ = new Mother_land(world_.get_grid(x, y), *this);

	world_.set_grid(motherland_, x, y);
}

void Faction::run() {
	if (motherland_ == nullptr) {
		//Loose
		die();
	} else {
		//Give money to colonies
		for (list<pair<Colonized_planet*,double> >::iterator itr = demands_.begin(); itr != demands_.end();itr++) {
            if (money_ - itr->second >= 0) {
                money_ -= itr->second;
                money_spent_ += itr->second;
				itr->first->add_to_budget(itr->second);
                cout << toString() << endl;
			}
		}
	}
}

void Faction::add_demand(Colonized_planet* demander, double cost) {
	demands_.push_back(std::pair< Colonized_planet*, double>(demander, cost));
}

void Faction::inc_nb_successful_attack_(){
    nb_successful_attack_++;
}

void Faction::inc_nb_failed_attack_(){
    nb_failed_attack_++;
}

string Faction::toString(){
    std::stringstream ss;
    ss << "Name :" << get_name() <<endl;
    ss << "Money : " << get_money() <<endl;
    ss << "Money produced : " << get_money_produce_() <<endl;
    ss << "Money spent : " << get_money_spent() <<endl;
    ss << "Number of colonies : " << colonies_.size() << endl;
    ss << "Number of attack : " << get_nb_failed_attack_() + get_nb_successful_attack_() << endl;
    ss << "Number of successful attack : " << get_nb_successful_attack_() << endl;
    ss << "Number of failed attack : " << get_nb_failed_attack_() << endl;
    ss << "----------------------------"<< endl;
    return ss.str();
}
