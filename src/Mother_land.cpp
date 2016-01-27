#include "Mother_land.hpp"

Mother_land::Mother_land(Virtual_planet* fp, Faction& fac) : Colonized_planet(fp, fac) {}

bool Mother_land::is_attacked(Virtual_planet *attacker) {
	bool res = Colonized_planet::is_attacked(attacker);
	if (res) {
		faction_.destroy_motherland();
	}
	return res;
}
