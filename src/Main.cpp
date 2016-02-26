
#include <iostream>
#include <random>
#include "World.hpp"



int main(int, char **) 
{
	World w1;
	w1.test3factions();
	w1.start();
	World::dispose();
	return 0;
}