#include "World.hpp"

time_h World::simulate(){
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
