#include "World.hpp"

World::World(std::mt19937& gen_mt, unsigned len, unsigned hei):
grid_(),
factions_(),waiting_agents_(),already_run_agents_(),
len_(len), hei_(hei),
gen_mt_(gen_mt)
{
	for (unsigned i = 0;i < len_;i++) {
		grid_.push_back(std::vector< Virtual_planet* >());
		for (unsigned j = 0; j < hei_;j++) {
			grid_[i].push_back(new Free_planet(*this, i, j));
		}
	}

	for (unsigned i = 0;i < len_;i++) {
		for (unsigned j = 0; j < hei_;j++) {
			((Free_planet*)grid_[i][j])->set_neighbourhood();
		}
	}

	//Creation of two initial factions
	factions_.push_back(Faction(*this, "Red"));
	factions_.push_back(Faction(*this, "Blue"));
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
		}
		return steps_;
}

void World::scheduler() {
	
	vector<Faction> factions_copy(factions_.begin(), factions_.end());

	random_shuffle(factions_copy.begin(), factions_copy.end());
	random_shuffle(waiting_agents_.begin(), waiting_agents_.end());
		
	for (vector<Faction>::iterator it = factions_copy.begin(); it != factions_copy.end(); it++ ) {
		it->run();
	}

	for (vector<Colonized_planet*>::iterator it = waiting_agents_.begin(); it != waiting_agents_.end(); it++) {
		(*it)->run();
  }
}

void World::display() {
	for (unsigned i = 0; i < hei()+2; i++) cout << "-";
	for (unsigned i = 0;i < hei(); i++) {
		for (unsigned j = 0;j < len();j++) {
			cout << "|";

			Faction faction = get_grid(j, i)->get_faction();
			if (faction.get_name() == "Red") cout << "R";
			else if (faction.get_name() == "Blue") cout << "B";
			else cout << "N";

			cout << "|";
		}
	}
	for (unsigned i = 0; i < hei()+2; i++) cout << "-";
}

int World::gen_mt() {
	return gen_mt_();
}

Virtual_planet* World::get_grid(unsigned x, unsigned y) {
	return grid_[x][y];
}

void World::set_grid(Virtual_planet* planet, unsigned x, unsigned y) {
	grid_[x][y] = planet;
}
