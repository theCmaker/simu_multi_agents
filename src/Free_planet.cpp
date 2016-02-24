#include "Free_planet.hpp"
#include "World.hpp"

Free_planet::Free_planet(World& world, unsigned pos_x, unsigned pos_y) :Virtual_planet(world, pos_x, pos_y) {}

Free_planet::Free_planet(Colonized_planet *other) : 
	Virtual_planet(other->get_world(), other->pos_x(), other->pos_y()) 
{
	for (unsigned i = 0 ; i < other->get_neighbourhood().size() ; i++) {
		other->get_neighbourhood()[i]->update_neighbourhood(other, this);
	}
}

void Free_planet::run() {

}

bool Free_planet::is_attacked(Virtual_planet *) {
    bool res = true;
    if(world_.gen_mt(0,4)==0){ //Une chance sur 5 de ne pas réussir
        res=false;
    }
    return res;
}
