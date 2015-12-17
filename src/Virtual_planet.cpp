#include "Virtual_planet.hpp"

Virtual_planet::Virtual_planet(World& world, unsigned pos_x, unsigned pos_y): world_(world), pos_x_(pos_x), pos_y_(pos_y) {
	production_rate_ = (double)(world_.mt() % 20);
	natural_defense_ = (double)(world_.mt() % 20);
}