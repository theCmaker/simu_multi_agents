#include "World.hpp"
#include <iostream>
#include <exception>

/*!
 * \brief Constructeur
 * \param len Nombre de planètes par ligne
 * \param hei Nombre de planètes par colonne
 */
World::World(unsigned len, unsigned hei):
end_(false),
grid_(),
factions_(),
waiting_agents_(),
already_run_agents_(),
steps_(0),
nb_simulated_agents_(0),
nb_attacks_success_(0),
nb_attacks_failed_(0),
stats_factions_(),
len_(len),
hei_(hei)
{
  for (unsigned i = 0 ; i < len_ ; i++) {
		grid_.push_back(std::vector< Virtual_planet* >());
		for (unsigned j = 0 ; j < hei_ ; j++) {
			grid_[i].push_back(new Free_planet(*this, i, j));
		}
	}

	for (unsigned i = 0 ; i < len_ ; i++) {
		for (unsigned j = 0 ; j < hei_ ; j++) {
			grid_[i][j]->set_neighbourhood();
		}
	}
}

/*!
 * \brief Destructeur
 */
World::~World() {
	for (unsigned i = 0 ; i < len_ ; i++) {
		for (unsigned j = 0 ; j < hei_ ; j++) {
			delete grid_[i][j];
		}
	}
}

/*!
 * \brief Lance la simulation
 * \return Nombre de tours joués jusqu'à la fin du jeu
 */
time_h World::start(){
  if(factions_.size() == 0){
    //std::string str;
    //str = "No faction created";
    throw new std::exception();
  }
  steps_ = 0;
  while (!end_) { //While there is no peace in the galaxy
		scheduler();
		if (DEBUG) { display(); }
	}
	if(factions_.size()==1) add_stat_faction(factions_.back());
	return steps_;
}

/*!
 * \brief Ordonnanceur
 *
 * Réalise un tirage aléatoire de l'ordre de passage des agents.
 *
 * Lance l'exécution de chaque faction en réponse aux attaques du tour précédent.
 *
 * Supprime les factions qui n'ont pas survécu aux attaques.
 *
 * Lance l'exécution de chaque planète, agent par agent selon l'ordre défini.
 *
 * Détermine si le jeu est terminé (i.e. s'il ne reste plus qu'une faction en jeu)
 */
void World::scheduler() {
	vector<Faction*> factions_to_delete;
	Faction* faction_to_delete;
	
	random_shuffle(waiting_agents_.begin(), waiting_agents_.end(), gen_mt_shuffle);
  
    for (list<Faction>::iterator it = factions_.begin() ; it != factions_.end() ; it++) {
        //if (DEBUG) cout << factions_copy[i].get_name() << " played !" << endl;
				faction_to_delete = it->run();
        if (faction_to_delete != nullptr) {
            factions_to_delete.push_back(faction_to_delete);
        }
    }

    //Suppression des factions a supprimer
    for (unsigned i = 0 ; i < factions_to_delete.size() ; i++) {
        remove_faction(factions_to_delete[i]);
    }

    for (unsigned i = 0 ; i < waiting_agents_.size() ; i++) {
        //if (DEBUG) cout << "(" << waiting_agents_[i]->pos_x() << "," << waiting_agents_[i]->pos_y() << ") played !" << endl;
				waiting_agents_[i]->run();
    }

    if (factions_.size() <= 1) end_ = true;
    ++steps_;
}

/*!
 * \brief Exemple de simulation avec 2 factions
 */
void World::test2factions(){
    //Creation of two initial factions

    factions_.push_back(Faction(*this,"Red"));
    factions_.back().init();
    factions_.back().set_motherland_symbol('R');
    factions_.back().set_colony_symbol('r');
    factions_.back().set_colony_color_name("red");
    factions_.back().set_motherland_color_name("darkRed");
    Faction& red = factions_.back();

    factions_.push_back(Faction(*this, "Blue"));
    factions_.back().init();
    factions_.back().set_motherland_symbol('B');
    factions_.back().set_colony_symbol('b');
    factions_.back().set_colony_color_name("blue");
    factions_.back().set_motherland_color_name("darkBlue");
    Faction& blue = factions_.back();

    if (DEBUG) {
        cout << "Red on :\t (" << red.get_motherland_()->pos_x() << "," << red.get_motherland_()->pos_y() << ")" << endl;
        cout << "Blue on :\t (" << blue.get_motherland_()->pos_x() << "," << blue.get_motherland_()->pos_y() << ")" << endl;
    }
}

/*!
 * \brief Exemple de simulation avec 3 factions
 */
void World::test3factions(){
    //Creation of three initial factions
    test2factions();

    factions_.push_back(Faction(*this, "Green"));
    factions_.back().init();
    factions_.back().set_motherland_symbol('G');
    factions_.back().set_colony_symbol('g');
    factions_.back().set_colony_color_name("green");
    factions_.back().set_motherland_color_name("darkGreen");
    Faction& green = factions_.back();

    if (DEBUG) {
        cout << green.get_name() << " on :\t (" << green.get_motherland_()->pos_x() << "," << green.get_motherland_()->pos_y() << ")" << endl;
    }
}

/*!
 * \brief Exemple de simulation avec 4 factions
 */
void World::test4factions(){
    //Creation of four initial factions
    test3factions();

    factions_.push_back(Faction(*this, "Yellow"));
    factions_.back().init();
    factions_.back().set_motherland_symbol('Y');
    factions_.back().set_colony_symbol('y');
    factions_.back().set_colony_color_name("yellow");
    factions_.back().set_motherland_color_name("darkYellow");
    Faction& yellow = factions_.back();

    if (DEBUG) {
        cout << yellow.get_name() << " on :\t (" << yellow.get_motherland_()->pos_x() << "," << yellow.get_motherland_()->pos_y() << ")" << endl;
    }
}

/*!
 * \brief Affichage de la grille
 * \note Pour le mode console
 */
void World::display() {
	for (unsigned i = 0 ; i < len() +2 ; i++) cout << "-";cout << endl;
	cout << "x|";
	for (unsigned i = 0 ; i < len() ; i++) cout << /*"|"<<*/ i%10 <<"|";cout << endl;


	for (unsigned i = 0 ; i < hei() ; i++) {
		cout <</* "|" <<*/ i%10 << "|";
		for (unsigned j = 0 ; j < len() ; j++) {
            cout << get_grid(j,i)->display();
            cout << "|";
		}
		cout << endl;
	}
	for (unsigned i = 0 ; i < len() + 2 ; i++) cout << "-";
	cout << endl << endl;

	cout << "Stats faction :" << endl;
    for (list<Faction>::iterator it = factions_.begin() ; it!=factions_.end() ; it++) {
        cout << it->toString();
	}
	cout << endl << endl;

	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));	//wait a second
}

/*!
 * \brief Ajout d'un agent à la liste d'attente
 * \param colonized_planet planète à ajouter
 */
void World::add_waiting_agent(Colonized_planet* colonized_planet) {
	waiting_agents_.push_back(colonized_planet);
}

/*!
 * \brief Suppression d'un agent de la liste d'attente
 * \param colonized_planet planète à supprimer
 */
void World::remove_waiting_agent(Colonized_planet* colonized_planet) {
	waiting_agents_.erase(std::remove(waiting_agents_.begin(), waiting_agents_.end(), colonized_planet),
	  waiting_agents_.end());	//search and remove
}

/*!
 * \brief Suppression définitive d'une faction
 * \param faction faction à supprimer
 */
void World::remove_faction(Faction* faction) {
	//std::cout << "suppression definitive de la faction " << faction->get_name() << std::endl;
	Faction & faction_to_remove = *faction;
    std::list<Faction>::iterator itr = std::find( factions_.begin(), factions_.end(), faction_to_remove);
	factions_.erase(itr);
}

/*!
 * \brief Générateur aléatoire (Mersenne Twister)
 * \return entier aléatoire
 */
int World::gen_mt() {
	return abs((int)gen_mt_());
}

/*!
 * \brief Générateur aléatoire borné supérieurement
 * \param i borne supérieure (intervalle ouvert)
 * \return entier aléatoire entre 0 et i
 */
int World::gen_mt_shuffle(int i) {
	return abs((int)gen_mt_())%i;
}

/*!
 * \brief Générateur aléatoire borné par un intervalle
 * \param a borne inférieure
 * \param b borne supérieure
 * \return entier aléatoire entre a et b
 */
int World::gen_mt(int a, int b) {
	return a + (int)(abs((int)gen_mt_())%(b - a + 1));
}

/*!
 * \brief Nettoie la faction neutre
 */
void World::dispose() {
    Neutral_faction::dispose();
}

/*!
 * \brief Planète dans la grille
 * \param x ligne où se trouve la planète
 * \param y colonne où se trouve la planète
 * \return planète à la position (x,y)
 */
Virtual_planet* World::get_grid(unsigned x, unsigned y) {
	return grid_[x][y];
}

/*!
 * \brief Installe une planète dans la grille
 * \param planet planète à insérer
 * \param x ligne de destination
 * \param y colonne de destination
 */
void World::set_grid(Virtual_planet* planet, unsigned x, unsigned y) {
	grid_[x][y] = planet;
}

/*!
 * \brief Liste des factions
 * \return liste
 */
std::list<Faction> World::get_factions() {
    return factions_;
}

/*!
 * \brief to string
 * \return texte représentant les valeurs courante du jeu
 */
string World::toString(){
    stringstream ss;
    ss << "Step #" << steps_ << endl;
    ss << "Factions :" << endl;
    ss << "----------------------------" << endl;
    for(std::list<Faction>::iterator it = factions_.begin() ; it != factions_.end() ; it++) {
        ss << it->toString();
    }
    return ss.str();
}

/*!
* \brief Statistiques
* \return texte formaté représentant les statistiques finales de jeu
*/
string World::stats_general() {
	stringstream ss;
	//ss << "Statistique generale" << endl;

	//ss << "Nombre de tours ;" << "Faction gagnante ;" << "Nombre d'attaques reussites ;" << "Nombre d'attaques echouees ;" << "Nombre d'attaques total" << endl;
	ss << steps_ << ";" << get_winner_name() << ";" << nb_attacks_success_ << ";" << nb_attacks_failed_ << ";" << nb_attacks_failed_ + nb_attacks_success_ << endl;

	return ss.str();
}

/*!
* \brief Statistiques
* \return texte formaté représentant les statistiques finales des factions
*/
string World::stats_faction() {
	stringstream ss;

//	ss << "Statistique des factions" << endl;
	for (list<string>::iterator it = stats_factions_.begin(); it != stats_factions_.end(); it++) {
		ss << *it << ";;";
	}
	ss << endl;

	return ss.str();
}

/*!
 * \brief Nom de la faction gagnante
 * \return nom de la faction gagnante
 */
string World::get_winner_name(){
    string res("[World]nofaction");
    if (factions_.size() == 1){
        res = factions_.back().get_name();
    }
    return res;
}

/*!
* \brief Ajout dans la liste des statistiques de faction et mise a jour des statistiques generales
* \param faction Faction a archiver dans les statisiques
*/
void World::add_stat_faction(Faction& faction) {
	stats_factions_.push_back(faction.stats());
	nb_attacks_failed_ += faction.get_nb_failed_attack_();
	nb_attacks_success_ += faction.get_nb_successful_attack_();
}

std::mt19937 World::gen_mt_ = std::mt19937();
