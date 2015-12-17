#include "Free_planet.hpp"

Free_planet::Free_planet(World& world, unsigned pos_x, unsigned pos_y) :Virtual_planet(world, pos_x, pos_y) {}

void Free_planet::set_neighbourhood() {
	
	/*********************************/
	/*        CODE A AMELIORER       */
	/*********************************/


	if (pos_x_ - 1 >= 0 && pos_y_ - 1 >= 0)		neighbourhood_.push_back(*(world_.grid(pos_x_ - 1, pos_y_ - 1)));
	if (pos_x_ - 1 >= 0 && pos_y_ >= 0)				neighbourhood_.push_back(*(world_.grid(pos_x_ - 1, pos_y_)));
	if (pos_x_ - 1 >= 0 && pos_y_ + 1 >= 0)		neighbourhood_.push_back(*(world_.grid(pos_x_ - 1, pos_y_ + 1)));

	if (pos_x_ >= 0 && pos_y_ - 1 >= 0)				neighbourhood_.push_back(*(world_.grid(pos_x_, pos_y_ - 1)));
	if (pos_x_ >= 0 && pos_y_ + 1 >= 0)				neighbourhood_.push_back(*(world_.grid(pos_x_, pos_y_ + 1)));

	if (pos_x_ + 1 >= 0 && pos_y_ - 1 >= 0)		neighbourhood_.push_back(*(world_.grid(pos_x_ + 1, pos_y_ - 1)));
	if (pos_x_ + 1 >= 0 && pos_y_ >= 0)				neighbourhood_.push_back(*(world_.grid(pos_x_ + 1, pos_y_)));
	if (pos_x_ + 1 >= 0 && pos_y_ + 1 >= 0)		neighbourhood_.push_back(*(world_.grid(pos_x_ + 1, pos_y_ + 1)));

}