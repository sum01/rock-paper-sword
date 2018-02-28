#include "moveset.hpp"

// ~~ Initializers ~~
Moveset::sword::sword() {
	this->set_dmg(4);
	// Sword can be blocked
	this->set_block_reduces(true);
}

Moveset::fireball::fireball() {
	this->set_dmg(3);
	// Fireball is not reduces by block
	this->set_block_reduces(false);
}

Moveset::shieldbash::shieldbash() {
	// 2 is so that if it's blocked then it's 1
	this->set_dmg(2);
	// The shieldbash can also be blocked
	this->set_block_reduces(true);
}

// ~~ Attacks ~~
int Moveset::sword::swing(bool was_blocked) {
	return this->calc_dmg(was_blocked);
}

int Moveset::fireball::cast() {
	// Since fireball can't be blocked, pass false
	return this->calc_dmg(false);
}

int Moveset::shieldbash::bash(bool was_blocked) {
	return this->calc_dmg(was_blocked);
}
