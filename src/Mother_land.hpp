#ifndef __MOTHER_LAND_H__
#define __MOTHER_LAND_H__

#include "Colonized_planet.hpp"
#include "World.hpp"

/*!
 * \brief Planète mère
 *
 * Dirige une faction
 *
 * @see Faction
 */
class Mother_land : public Colonized_planet
{
public:
    Mother_land(Virtual_planet*,Faction&);

    char        display         () {return faction_.get_motherland_symbol();}       //!< Caractère représentant la planète mère
    std::string get_color_name  () {return faction_.get_motherland_color_name();}   //!< Couleur représentant la planète mère
    bool        is_attacked     (Virtual_planet *);
};

#endif
