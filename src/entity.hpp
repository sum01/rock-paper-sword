#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "moveset.hpp"
#include <string>

namespace Entity {
// Inherit our moveset so we can cast spells, swing a sword, and shield bash
class entity : public Moveset::sword, public Moveset::fireball, public Moveset::shieldbash {
protected:
	// Entity's health
	int hp;
	// Hold a name for printing out
	std::string name;
public:
	// An inizializer for setting the name
	explicit entity(std::string);
	std::string get_name();
	int get_hp();
	// Resets/sets hp to full
	void full_hp();
	// Take off some health
	void reduce_hp(int);
	void print_hp();
};
}

#endif
