#ifndef __FACTION_H__
#define __FACTION_H__

#include <string>
#include <list>
#include <sstream>

class World;
class Mother_land;
class Colonized_planet;

class Faction
{
private:
    World&										world_;

	std::string									name_;
    double										money_;
	Mother_land								*	motherland_;
    std::list<Colonized_planet*>                colonies_;
    char                                        colony_symbol_;
    char                                        motherland_symbol_;
    char *                                      colony_color_name_;
    char *                                      motherland_color_name_;

	std::list<std::pair<Colonized_planet*, double> > demands_;

    //stats
    double money_spent_;
    double money_produce_;
    int nb_successful_attack_;
    int nb_failed_attack_;

	//private methods
	void loose();

public:
	
	Faction(World& world, std::string name = "default", Mother_land* = nullptr );	//Create a faction and convert a free planete into a mother land
	~Faction();

	void run();
	void init();
	void die();

    Faction& operator= (Faction) {return *this;}

	bool operator== (const Faction &other) const {return this->name_ == other.name_;}
	bool operator== (Faction &other) { return this->name_ == other.name_; }

	//Getter setter
	std::string   get_name() {return name_;}
	double        get_money() {return money_;}
    char          get_motherland_symbol() { return motherland_symbol_;}
    char          get_colony_symbol() { return colony_symbol_;}
    char*         get_colony_color_name() {return colony_color_name_;}
    char*         get_motherland_color_name() {return motherland_color_name_;}
	Mother_land*  get_motherland_() {return motherland_;}
	std::list<Colonized_planet*> & get_colonies() {return colonies_;}

	void add_colony(Colonized_planet* colony) {colonies_.push_back(colony);}
	void remove_colony(Colonized_planet* colony);
	void remove_mother_land();
    void add_to_banque(double);

    void set_colony_symbol(char c) { colony_symbol_ = c;}
    void set_motherland_symbol(char c) { motherland_symbol_ = c;}
    void set_colony_color_name(char* colony_color_name) { colony_color_name_ = colony_color_name;}
    void set_motherland_color_name(char* motherland_color_name) { motherland_color_name_ = motherland_color_name;}
	void add_demand(Colonized_planet*, double);

    //stat
    double get_money_spent(){ return money_spent_;}
    double get_money_produce_(){return money_produce_;}
    int get_nb_successful_attack_(){return nb_successful_attack_;}
    int get_nb_failed_attack_(){return nb_failed_attack_;}
    void inc_nb_successful_attack_();
    void inc_nb_failed_attack_();

    std::string toString();
};

#endif
