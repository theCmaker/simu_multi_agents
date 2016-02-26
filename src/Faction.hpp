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
  World&										      world_;
	std::string								      name_;
  double										      money_;
	Mother_land							     *	motherland_;
  char                            motherland_symbol_;
  std::list<Colonized_planet*>    colonies_;
  char                            colony_symbol_;
  std::string                     colony_color_name_;
  std::string                     motherland_color_name_;

	std::list<std::pair<Colonized_planet*, double> > demands_;

  //stats
  double  money_spent_;
  double  money_produce_;
  int     nb_successful_attack_;
  int     nb_failed_attack_;

	//private methods
	void loose();

public:
	
	Faction(World& world, std::string name = "default", Mother_land* = nullptr);	//Create a faction and convert a free planete into a mother land
  Faction& operator= (Faction) {return *this;}

  //Comparators
	bool operator== (const Faction &other) const {return this->name_ == other.name_;}
	bool operator== (Faction &other)             {return this->name_ == other.name_; }
  
  //Actions
  Faction * run();
  void      init();
  void      die();

	//Getters
	std::string   get_name                     () {return name_;}
	double        get_money                    () {return money_;}
  char          get_motherland_symbol        () {return motherland_symbol_;}
  char          get_colony_symbol            () {return colony_symbol_;}
  std::string   get_colony_color_name        () {return colony_color_name_;}
  std::string   get_motherland_color_name    () {return motherland_color_name_;}
	Mother_land*  get_motherland_              () {return motherland_;}
	std::list<Colonized_planet*> & get_colonies() {return colonies_;}

  //Methods
	void add_colony          (Colonized_planet* colony) {colonies_.push_back(colony);}
	void remove_colony       (Colonized_planet* colony);
	void remove_mother_land  ();
	void remove_demand       (Colonized_planet* colony);
  void add_to_banque       (double);

  //Setters
  void set_colony_symbol        (char c)                            { colony_symbol_ = c;}
  void set_motherland_symbol    (char c)                            { motherland_symbol_ = c;}
  void set_colony_color_name    (std::string colony_color_name)     { colony_color_name_ = colony_color_name;}
  void set_motherland_color_name(std::string motherland_color_name) { motherland_color_name_ = motherland_color_name;}
	void add_demand               (Colonized_planet*, double);

  //stat
  double  get_money_spent           () {return money_spent_;}
  double  get_money_produce_        () {return money_produce_;}
  int     get_nb_successful_attack_ () {return nb_successful_attack_;}
  int     get_nb_failed_attack_     () {return nb_failed_attack_;}
  void    inc_nb_successful_attack_ ();
  void    inc_nb_failed_attack_     ();

  //Display
  std::string toString();
};


class Comparator {
private:
  Colonized_planet* colonized_planet_;
public:
  Comparator(Colonized_planet* colonized_planet) {
    colonized_planet_ = colonized_planet;
  }

  bool operator()(std::pair<Colonized_planet*,double> pair_colony) {
    return pair_colony.first == colonized_planet_;
  }
};
#endif
