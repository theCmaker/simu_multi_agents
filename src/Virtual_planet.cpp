#include "Virtual_planet.hpp"
#include "World.hpp"

Virtual_planet::Virtual_planet(World& world, unsigned pos_x, unsigned pos_y):
	world_(world),
	pos_x_(pos_x),
    pos_y_(pos_y),
    changed_(true)
{
    production_rate_ = (double)(World::gen_mt(0,10));
    natural_defense_ = (double)(World::gen_mt(25,50));
}

Virtual_planet::Virtual_planet(Virtual_planet *other) :
	world_(other->world_),
	pos_x_(other->pos_x_),
	pos_y_(other->pos_y_),
	neighbourhood_(),
	production_rate_(other->production_rate_),
	natural_defense_(other->natural_defense_)
	{
		for (unsigned i=0 ; i<other->neighbourhood_.size() ; i++){
			neighbourhood_.push_back(other->neighbourhood_[i]);
		}
}

void Virtual_planet::set_neighbourhood2() {
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
}

void Virtual_planet::set_neighbourhood() {
	bool dosmth;
	neighbourhood_.clear();
	for (int i = -1;i<=1;i++) {
		for (int j = -1;j<=1;j++) {
			dosmth = true;
			if (((int)pos_x_) + i<0 || ((int)pos_y_) + j<0) {
				dosmth = false;
			}

			if (((int)pos_x_) + i >= (int)world_.len() || ((int)pos_y_) + j >= (int)world_.hei()) {
				dosmth = false;
			}

			if (i == 0 && j == 0) {
				dosmth = false;
			}
			if (dosmth) {
				neighbourhood_.push_back(world_.get_grid(((int)pos_x_) + i, ((int)pos_y_) + j));
			}
		}
	}
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

Faction& Virtual_planet::get_faction() {
    Faction* test =Neutral_faction::get_instance(world_);
    return *test;
}

bool Virtual_planet::has_changed(){
    bool res = changed_;
    if (changed_)   changed_=false;
    return res;
}

void Virtual_planet::change(){
    changed_=true;
}


std::ostream & operator<< (std::ostream &o, Virtual_planet &vp) {
	o << "Planet at (" << vp.pos_x() <<  ',' << vp.pos_y() << ") of faction " << vp.get_faction().get_name();
	return o;
}
