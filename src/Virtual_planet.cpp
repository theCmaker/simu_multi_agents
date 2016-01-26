#include "Virtual_planet.hpp"
#include "World.hpp"

Virtual_planet::Virtual_planet(World& world, unsigned pos_x, unsigned pos_y):
	world_(world),
	pos_x_(pos_x),
	pos_y_(pos_y),
	faction_neutre_(world_,"Neutral") {
	production_rate_ = (double)(world_.gen_mt() % 20);
	natural_defense_ = (double)(world_.gen_mt() % 20);
}

Virtual_planet::Virtual_planet(const Virtual_planet &other) :
	world_(other.world_),
	pos_x_(other.pos_x_),
	pos_y_(other.pos_y_),
	neighbourhood_(),
	production_rate_(other.production_rate_),
	natural_defense_(other.natural_defense_),
	faction_neutre_(other.faction_neutre_){
		for (unsigned i=0 ; i<other.neighbourhood_.size() ; i++){
			neighbourhood_.push_back(other.neighbourhood_[i]);
		}
}

void Virtual_planet::set_neighbourhood() {
	/*if (((int)pos_x_ - 1) >= 0 && ((int) pos_y_ - 1) >= 0)		neighbourhood_.push_back(world_.get_grid(pos_x_ - 1, pos_y_ - 1));
	if (((int)pos_x_ - 1) >= 0 && ((int)pos_y_) >= 0)				neighbourhood_.push_back(world_.get_grid(pos_x_ - 1, pos_y_));
	if (((int)pos_x_ - 1) >= 0 && ((int)pos_y_ + 1) >= 0)		neighbourhood_.push_back(world_.get_grid(pos_x_ - 1, pos_y_ + 1));

	if ((int) pos_x_ >= 0 && ((int) pos_y_ - 1) >= 0)				neighbourhood_.push_back(world_.get_grid(pos_x_, pos_y_ - 1));
	if ((int) pos_x_ >= 0 && ((int) pos_y_ + 1) >= 0)				neighbourhood_.push_back(world_.get_grid(pos_x_, pos_y_ + 1));

	if (((int)pos_x_ + 1) >= 0 && ((int)pos_y_ - 1) >= 0)		neighbourhood_.push_back(world_.get_grid(pos_x_ + 1, pos_y_ - 1));
	if (((int)pos_x_ + 1) >= 0 && (int)pos_y_ >= 0)				neighbourhood_.push_back(world_.get_grid(pos_x_ + 1, pos_y_));
	if (((int)pos_x_ + 1) >= 0 && ((int)pos_y_ + 1) >= 0)		neighbourhood_.push_back(world_.get_grid(pos_x_ + 1, pos_y_ + 1));*/
	//bool dosmth;
	
	for (int i = -1 ; i < 2 ; ++i) {
	  for (int j = -1 ; j < 2 ; ++j) {
	    if ( i != 0 || j != 0)
	      neighbourhood_.push_back(world_.get_grid((((int)pos_x_) + i)%world_.len(), ((((int)pos_y_) + j)%world_.hei())));
	  }
	}
	/*
	for (int i=-1;i<1;i++){
		for(int j=-1;j<1;j++){
			dosmth=true;
			if(((int)pos_x_)+i<0 || ((int)pos_y_)+j<0){
				dosmth=false;
			}
			
			if(((int)pos_x_)+i >= (int)world_.len() || ((int)pos_y_)+j >= (int)world_.hei()){
				dosmth=false;
			}
			
			if(i==0 && j==0){
				dosmth=false;
			}
			if(dosmth){
			  cout << "coucou" << endl;
				neighbourhood_.push_back(world_.get_grid(((int)pos_x_) + i, ((int)pos_y_) + j));
			}
		}
	}
	*/
	
  /*std::cout << neighbourhood_.size() << std::endl;
	for (auto i : neighbourhood_) {
	  cout << i->pos_x() << ' ' << i->pos_y() << endl;
	} 
	*/
}

void Virtual_planet::update_neighbourhood(Virtual_planet *old_one,Virtual_planet *new_one) {
	std::vector<Virtual_planet *>::iterator itr= std::find(neighbourhood_.begin(),neighbourhood_.end(),old_one);
	if (itr != neighbourhood_.end()) {
		*itr = new_one;
	}
}

void Virtual_planet::run() {
	//Non utilisé
}
