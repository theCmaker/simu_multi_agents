#ifndef NEUTRAL_FACTION_H
#define NEUTRAL_FACTION_H

#include "Faction.hpp"

class Neutral_faction : public Faction
{
private:
    static Neutral_faction* instance_;
    Neutral_faction(World& world);
public:
    static Neutral_faction* get_instance(World& world);
};

#endif // NEUTRAL_FACTION_H
