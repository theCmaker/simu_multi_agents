#include "Free_planet.hpp"
#include "World.hpp"

Free_planet::Free_planet(World& world, unsigned pos_x, unsigned pos_y) :Virtual_planet(world, pos_x, pos_y) {}


void Free_planet::run() {

}

bool Free_planet::is_attacked(Virtual_planet *) {
	return true;
}
