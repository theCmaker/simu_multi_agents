#include "World.hpp"

World::World(std::mt19937& gen_mt, unsigned len = 20, unsigned hei = 20):
gen_mt_(gen_mt), len_(len), hei_(hei),
grid_(len, std::vector<Virtual_planet*>(hei))
{
	for (unsigned i = 0;i < len_;i++) {
		for (unsigned j = 0; j < hei_;j++) {
			grid_[i][j] = new Free_planet(*this,i,j);
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
    while(factions_.size()>1){ //While there is no peace in the galaxy
        scheduler();
        ++steps_;
    }
}

void World::scheduler() {
    for (std::list<Faction>::iterator i = factions_.begin(); i != factions_.end(); ++i) {
      
    }
    waiting_agents_.swap(already_run_agents_); 
}

int World::mt() {
	return gen_mt_();
}

Virtual_planet* World::grid(unsigned x, unsigned y) {
	return grid_[x][y];
}
