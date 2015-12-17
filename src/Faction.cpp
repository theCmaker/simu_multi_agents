#include "Faction.hpp"

Faction::Faction(World& world, std::string name):
world_(world), name_(name),money_(0),motherland_(nullptr),colonies_()
{
	//Find the mother_land
	unsigned x = world_.mt() % world_.len;
	unsigned y = world_.mt() % world_.hei;


	/*WARNING : WHAT HAPPENS IF THE PLANET ISNT FREE */

//	(Free_planet)(world_.grid(x,y))->
}