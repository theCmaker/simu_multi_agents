
#include <iostream>
#include <random>
#include "World.hpp"



int main(int argc, char *argv[]) 
{
	std::mt19937 mt;
	World w1(mt);
	w1.start();
	return 0;
}