#ifndef ATTACK_HPP
#define ATTACK_HPP

namespace Attack {
class attack {
protected:
	// Describes the damage done by the attack
	int damage;
	// Describes if the attack can have dmg absorbed by a block
	bool block_reduces;
public:
	void set_dmg(int);
	void set_block_reduces(bool);
	int calc_dmg(bool);
};
}

#endif
