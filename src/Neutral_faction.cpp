#include "Neutral_faction.hpp"
#include <iostream>

Neutral_faction::Neutral_faction(World& world):
	Faction(world,"Neutral")
{
    instance_ = this;
}

Neutral_faction * Neutral_faction::get_instance(World& world) {
    if (instance_ == nullptr) {
        instance_ = new Neutral_faction(world);
    }
    return instance_;
}

void Neutral_faction::dispose() {
	delete instance_;
	instance_ = nullptr;
}


//Initialization
Neutral_faction* Neutral_faction::instance_ = nullptr;