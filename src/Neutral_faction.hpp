#ifndef NEUTRAL_FACTION_H
#define NEUTRAL_FACTION_H

#include "Faction.hpp"

/*!
 * \brief Faction neutre
 *
 * C'est la faction à laquelle appartiennent les planètes libres
 *
 * \note Modèle singleton
 * \todo à vérifier
 */
class Neutral_faction : public Faction
{
private:
    static Neutral_faction* instance_; //!< Instance (unique)
    Neutral_faction(World& world);

public:
    static Neutral_faction* get_instance(World& world);
    static void dispose();
};

#endif // NEUTRAL_FACTION_H
