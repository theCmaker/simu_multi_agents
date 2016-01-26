#include "World.hpp"

World::World(std::mt19937& gen_mt, unsigned len, unsigned hei):
grid_(),
factions_(),
waiting_agents_(),
already_run_agents_(),
len_(len),
hei_(hei),
gen_mt_(gen_mt),
neutral_faction_(*this,"Neutral")
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


	//Creation of two initial factions

	factions_.push_back(Faction(*this,"Red"));
	factions_.back().init();
	factions_.back().set_motherland_symbol('R');
	factions_.back().set_colony_symbol('r');
	Faction& red = factions_.back();

	factions_.push_back(Faction(*this, "Blue"));
	factions_.back().init();
	factions_.back().set_motherland_symbol('B');
	factions_.back().set_colony_symbol('b');
	Faction& blue = factions_.back();

	if (DEBUG) {
		cout << "Red on :\t (" << red.get_motherland_()->pos_x() << "," << red.get_motherland_()->pos_y() << ")" << endl;
		cout << "Blue on :\t (" << blue.get_motherland_()->pos_x() << "," << blue.get_motherland_()->pos_y() << ")" << endl;
	}
	
	//factions_.back().get_motherland_()->
}

World::~World() {
	for (unsigned i = 0;i < len_;i++) {
		for (unsigned j = 0; j < hei_;j++) {
			delete grid_[i][j];
		}
	}
}

time_h World::start(){
		while (factions_.size() > 1) { //While there is no peace in the galaxy
			scheduler();
			++steps_;
			display();
		}
		return steps_;
}

void World::scheduler() {
	
	vector<Faction> factions_copy(factions_.begin(), factions_.end());
	
	unsigned size=waiting_agents_.size();
	
	//Toujours le meme shuffle, le tirage des factions ne changent pas
	random_shuffle(factions_copy.begin(), factions_copy.end());
	random_shuffle(waiting_agents_.begin(), waiting_agents_.end());

  
  for (unsigned i =0; i<factions_copy.size();i++){
	  if (DEBUG) cout << factions_copy[i].get_name() << " played !" << endl;
		factions_copy[i].run();
  }

  for (unsigned i =0; i<size;i++){
	  if (DEBUG) cout << "(" << waiting_agents_[i]->pos_x() << "," << waiting_agents_[i]->pos_y() << ") played !" << endl;
		waiting_agents_[i]->run();
  }
  
}

void World::display() {
	for (unsigned i = 0; i < len() +2; i++) cout << "-";cout << endl;
	cout << "x|";
	for (unsigned i = 0; i < len(); i++) cout << /*"|"<<*/ i%10 <<"|";cout << endl;


	for (unsigned i = 0;i < hei(); i++) {
		cout <</* "|" <<*/ i%10 << "|";
		for (unsigned j = 0;j < len();j++) {
			/*cout << "|";*/

			//Faction faction = get_grid(j, i)->get_faction();
      cout << get_grid(j,i)->display();
			/*if (faction.get_name() == "Red") cout << "R";
			else if (faction.get_name() == "Blue") cout << "B";
			else cout << "N";*/

			cout << "|";
		}
		cout << endl;
	}
	for (unsigned i = 0; i < len() +2; i++) cout << "-";
	cout << endl <<endl;

	cout << "Stats faction :" << endl;
	for(Faction faction : factions_) {
		cout << "Name :" << faction.get_name() << endl;
		cout << "Money : " << faction.get_money() << endl;
		cout << "----------------------------" << endl;
	}
	cout << endl << endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));	//wait a second
}

void World::add_waiting_agent(Colonized_planet* colonized_planet) {
	waiting_agents_.push_back(colonized_planet);
}

void World::remove_waiting_agent(Colonized_planet* colonized_planet) {
	waiting_agents_.erase(std::remove(waiting_agents_.begin(), waiting_agents_.end(), colonized_planet),
		waiting_agents_.end());	//search and remove
}


void World::kill_faction(Faction& faction) {
	std::list<Faction>::iterator itr = std::find(factions_.begin(), factions_.end(), faction);
	factions_.erase(itr);
}

int World::gen_mt() {
	return abs((int)gen_mt_());
}

int World::gen_mt_shuffle(int i) {
	return abs((int)gen_mt_())%i;
}


int World::gen_mt(int a, int b) {
	return a + (int)(abs((int)gen_mt_()) / (double)gen_mt_.max())*(b-a);
}

Virtual_planet* World::get_grid(unsigned x, unsigned y) {
	return grid_[x][y];
}

void World::set_grid(Virtual_planet* planet, unsigned x, unsigned y) {
	grid_[x][y] = planet;
}

Faction& World::get_neutral_faction() {
	return neutral_faction_;
}
