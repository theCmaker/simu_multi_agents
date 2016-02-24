#ifndef __COLONIZED_PLANET_H__
#define __COLONIZED_PLANET_H__

#include "Free_planet.hpp"

class Colonized_planet : public Virtual_planet
{
public:
  
  //Colonized_planet(const Colonized_planet &);
  Colonized_planet(World &, unsigned, unsigned, Faction&);
  Colonized_planet(Virtual_planet *, Faction&);							//Transfome une free en colonise
	~Colonized_planet() {};

	void update_neighbourhood(Virtual_planet *, Virtual_planet *); //update changes to neighbourhood when planet is attacked.
	bool attack(Virtual_planet *);		//bool : success
	virtual bool is_attacked(Virtual_planet *);

	void convert_to_free_planet();

	Faction& get_faction();
	double get_defense();
    double get_production();
	Virtual_planet* get_target() { return target_; }

	void demand_to_faction(double);									//Execute a demande of money
    double estimate_cost();                                         //Estimate the cost of the colonization (and attack)
	void add_to_budget(double);
	void reinitialisate_target();

    char display() { return faction_.get_colony_symbol(); }
    char* get_color_name() { return faction_.get_colony_color_name();}
	bool run();


protected:
  double colony_defense_;
  double colony_production_;
	Faction& faction_;

	Virtual_planet* target_;
	double budget_;	//current money
	double demand_;	//Estimate cost
};

#endif
