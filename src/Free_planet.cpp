#include "Free_planet.hpp"
#include "World.hpp"

Free_planet::Free_planet(World& world, unsigned pos_x, unsigned pos_y) :Virtual_planet(world, pos_x, pos_y) {}

void Free_planet::set_neighbourhood() {
	
	/*********************************/
	/*        CODE A AMELIORER       */
	/*********************************/


	if (((int)pos_x_ - 1) >= 0 && ((int) pos_y_ - 1) >= 0)		neighbourhood_.push_back(world_.get_grid(pos_x_ - 1, pos_y_ - 1));
	if (((int)pos_x_ - 1) >= 0 && ((int)pos_y_) >= 0)				neighbourhood_.push_back(world_.get_grid(pos_x_ - 1, pos_y_));
	if (((int)pos_x_ - 1) >= 0 && ((int)pos_y_ + 1) >= 0)		neighbourhood_.push_back(world_.get_grid(pos_x_ - 1, pos_y_ + 1));

	if ((int) pos_x_ >= 0 && ((int) pos_y_ - 1) >= 0)				neighbourhood_.push_back(world_.get_grid(pos_x_, pos_y_ - 1));
	if ((int) pos_x_ >= 0 && ((int) pos_y_ + 1) >= 0)				neighbourhood_.push_back(world_.get_grid(pos_x_, pos_y_ + 1));

	if (((int)pos_x_ + 1) >= 0 && ((int)pos_y_ - 1) >= 0)		neighbourhood_.push_back(world_.get_grid(pos_x_ + 1, pos_y_ - 1));
	if (((int)pos_x_ + 1) >= 0 && (int)pos_y_ >= 0)				neighbourhood_.push_back(world_.get_grid(pos_x_ + 1, pos_y_));
	if (((int)pos_x_ + 1) >= 0 && ((int)pos_y_ + 1) >= 0)		neighbourhood_.push_back(world_.get_grid(pos_x_ + 1, pos_y_ + 1));

}