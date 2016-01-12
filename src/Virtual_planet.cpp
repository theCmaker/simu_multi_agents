#include "Virtual_planet.hpp"
#include "World.hpp"

Virtual_planet::Virtual_planet(World& world, unsigned pos_x, unsigned pos_y):
	world_(world), pos_x_(pos_x), pos_y_(pos_y) {
	production_rate_ = (double)(world_.gen_mt() % 20);
	natural_defense_ = (double)(world_.gen_mt() % 20);
}

/*Virtual_planet::Virtual_planet(const Virtual_planet &other):
	world_(old.world_), 
	pos_x_(old.pos_x_), 
	pos_y_(old.pos_y_),
	neighbourhood_(old.neighbourhood_) {
	production_rate_ = (double)(world_.gen_mt() % 20);
	natural_defense_ = (double)(world_.gen_mt() % 20);
}*/

void Virtual_planet::update_neighbourhood(Virtual_planet *old_one,Virtual_planet *new_one) {
	std::vector<Virtual_planet *>::iterator itr= std::find(neighbourhood_.begin(),neighbourhood_.end(),old_one);
	if (itr != neighbourhood_.end()) {
		*itr = new_one;
	}
}

void Virtual_planet::run() {
	//Non utilisé
}