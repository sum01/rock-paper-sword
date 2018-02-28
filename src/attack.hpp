#ifndef ATTACK_HPP
#define ATTACK_HPP

namespace Attack {
class attack {
protected:
	// Set defaults for safety
	int damage;
	bool block_reduces;
public:
	void set_dmg(int);
	void set_block_reduces(bool);
	int calc_dmg(bool);
};
}

#endif
