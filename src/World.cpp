#include "World.hpp"

World::World(unsigned len, unsigned hei):
end_(false),
grid_(),
factions_(),
waiting_agents_(),
already_run_agents_(),
len_(len),
hei_(hei)
//neutral_faction_(*this,"Neutral")
{
    for (unsigned i = 0;i < len_;i++) {
		grid_.push_back(std::vector< Virtual_planet* >());
		for (unsigned j = 0; j < hei_;j++) {
			grid_[i].push_back(new Free_planet(*this, i, j));
		}
	}

	for (unsigned i = 0;i < len_;i++) {
		for (unsigned j = 0; j < hei_;j++) {
			grid_[i][j]->set_neighbourhood();
		}
	}
}



World::~World() {
	for (unsigned i = 0;i < len_;i++) {
		for (unsigned j = 0; j < hei_;j++) {
			delete grid_[i][j];
		}
	}
}

time_h World::start(){
        if(factions_.size() == 0){
            throw new exception("No faction created !!");
        }
        steps_=0;
        while (!end_) { //While there is no peace in the galaxy
			scheduler();
			++steps_;
			display();
		}
		return steps_;
}

void World::scheduler() {
	vector<Faction*> factions_to_delete;
	Faction* faction_to_delete;
	
	//TODO bug -> toujours meme ordre de faction
	random_shuffle(waiting_agents_.begin(), waiting_agents_.end(), gen_mt_shuffle);
  
  for (list<Faction>::iterator it = factions_.begin(); it != factions_.end(); it++){
	//  if (DEBUG) cout << factions_copy[i].get_name() << " played !" << endl;
        faction_to_delete = it->run();
				if (faction_to_delete != nullptr) {
					factions_to_delete.push_back(faction_to_delete);
				}
  }

	//Suppression des faction a supprimer
    for (unsigned i = 0; i < factions_to_delete.size(); i++) {
		remove_faction(factions_to_delete[i]);
	}
	
  for (unsigned i =0; i< waiting_agents_.size();i++){
//	  if (DEBUG) cout << "(" << waiting_agents_[i]->pos_x() << "," << waiting_agents_[i]->pos_y() << ") played !" << endl;
		waiting_agents_[i]->run();
  }

  if(factions_.size()<=1) end_=true;
}

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

void World::test3factions(){
    //Creation of two initial factions
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

void World::test4factions(){
    //Creation of two initial factions
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

void World::display() {
	for (unsigned i = 0; i < len() +2; i++) cout << "-";cout << endl;
	cout << "x|";
	for (unsigned i = 0; i < len(); i++) cout << /*"|"<<*/ i%10 <<"|";cout << endl;


	for (unsigned i = 0;i < hei(); i++) {
		cout <</* "|" <<*/ i%10 << "|";
		for (unsigned j = 0;j < len();j++) {
            cout << get_grid(j,i)->display();
            cout << "|";
		}
		cout << endl;
	}
	for (unsigned i = 0; i < len() +2; i++) cout << "-";
	cout << endl <<endl;

	cout << "Stats faction :" << endl;
    for(list<Faction>::iterator it = factions_.begin(); it!=factions_.end(); it++ ) {
        cout << it->toString();
	}
	cout << endl << endl;

	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));	//wait a second
}

void World::add_waiting_agent(Colonized_planet* colonized_planet) {
	waiting_agents_.push_back(colonized_planet);
}

void World::remove_waiting_agent(Colonized_planet* colonized_planet) {
	waiting_agents_.erase(std::remove(waiting_agents_.begin(), waiting_agents_.end(), colonized_planet),
		waiting_agents_.end());	//search and remove
}


void World::remove_faction(Faction* faction) {
	std::cout << "suppression definitive de la faction " << faction->get_name() << std::endl;
	Faction& faction_to_remove = *faction;
    std::list<Faction>::iterator itr = std::find( factions_.begin(), factions_.end(), faction_to_remove);
	factions_.erase(itr);
}

int World::gen_mt() {
	return abs((int)gen_mt_());
}

int World::gen_mt_shuffle(int i) {
	return abs((int)gen_mt_())%i;
}


int World::gen_mt(int a, int b) {
	return a + (int)(abs((int)gen_mt_())%(b - a + 1));
}

Virtual_planet* World::get_grid(unsigned x, unsigned y) {
	return grid_[x][y];
}

void World::set_grid(Virtual_planet* planet, unsigned x, unsigned y) {
	grid_[x][y] = planet;
}

std::list<Faction> World::get_factions(){
    return factions_;
}

/*Faction& World::get_neutral_faction() {
    return neutral_faction_;
}*/

string World::stats(){
    stringstream ss;
    ss << "Factions :" << endl;
    ss << "----------------------------"<< endl;
    for(std::list<Faction>::iterator it = factions_.begin();
        it != factions_.end() ; it++){
        ss << it->toString();
    }
    return ss.str();
}

string World::get_winner_name(){
    string res("[World]nofaction");
    if (factions_.size()==1){
        res=factions_.back().get_name();
    }
    return res;
}

std::mt19937 World::gen_mt_=std::mt19937();
