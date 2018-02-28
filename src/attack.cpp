#include "attack.hpp"
// For rounding
#include <cmath>
// Tell them they were blocked
#include <iostream>

void Attack::attack::set_dmg(int dmg) {
	this->damage = dmg;
}

void Attack::attack::set_block_reduces(bool reduces) {
	this->block_reduces = reduces;
}

// Returns the dmg that would be done by the attack
int Attack::attack::calc_dmg(bool was_blocked) {
	// If the attack is reduced by a block, and was blocked, halve its dmg
	if (this->block_reduces && was_blocked) {
		// Round up for whole number damage
		return std::ceil(this->damage / 2);
	} else {
		// Otherwise return the full dmg
		return this->damage;
	}
}
