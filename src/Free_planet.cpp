#include "Free_planet.hpp"
#include "World.hpp"

Free_planet::Free_planet(World& world, unsigned pos_x, unsigned pos_y) :Virtual_planet(world, pos_x, pos_y) {}

void Free_planet::set_neighbourhood() {
	/*if (((int)pos_x_ - 1) >= 0 && ((int) pos_y_ - 1) >= 0)		neighbourhood_.push_back(world_.get_grid(pos_x_ - 1, pos_y_ - 1));
	if (((int)pos_x_ - 1) >= 0 && ((int)pos_y_) >= 0)				neighbourhood_.push_back(world_.get_grid(pos_x_ - 1, pos_y_));
	if (((int)pos_x_ - 1) >= 0 && ((int)pos_y_ + 1) >= 0)		neighbourhood_.push_back(world_.get_grid(pos_x_ - 1, pos_y_ + 1));

	if ((int) pos_x_ >= 0 && ((int) pos_y_ - 1) >= 0)				neighbourhood_.push_back(world_.get_grid(pos_x_, pos_y_ - 1));
	if ((int) pos_x_ >= 0 && ((int) pos_y_ + 1) >= 0)				neighbourhood_.push_back(world_.get_grid(pos_x_, pos_y_ + 1));

	if (((int)pos_x_ + 1) >= 0 && ((int)pos_y_ - 1) >= 0)		neighbourhood_.push_back(world_.get_grid(pos_x_ + 1, pos_y_ - 1));
	if (((int)pos_x_ + 1) >= 0 && (int)pos_y_ >= 0)				neighbourhood_.push_back(world_.get_grid(pos_x_ + 1, pos_y_));
	if (((int)pos_x_ + 1) >= 0 && ((int)pos_y_ + 1) >= 0)		neighbourhood_.push_back(world_.get_grid(pos_x_ + 1, pos_y_ + 1));*/
	
	bool dosmth;
	
	for (int i=-1;i<1;i++){
		for(int j=-1;j<1;j++){
			dosmth=true;
			if(pos_x_+i<0 || pos_y_+j<0){
				dosmth=false;
			}
			
			if(pos_x_+i>=world.len() || pos_y_+j>=world.hei()){
				dosmth=false;
			}
			
			if(i==0 && j==0){
				dosmth=false;
			}
			
			if(dosmth){
				neighbourhood_.push_back(world_.get_grid(pos_x_ + i, pos_y_ + j));
			}
		}
	}

}

void Free_planet::run() {

}
