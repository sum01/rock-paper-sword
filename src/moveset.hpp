#ifndef MOVESET_HPP
#define MOVESET_HPP

#include "attack.hpp"

// Define our available moveset
namespace Moveset {
// The sword attack
class sword : private Attack::attack {
public:
	// Initializes inherited Attack::attack values
	explicit sword();
	int swing(bool);
};
// The fireball attack
class fireball : private Attack::attack {
public:
	// Initializes inherited Attack::attack values
	explicit fireball();
	int cast();
};
// The shield bash attack
class shieldbash : private Attack::attack {
public:
	// Initializes inherited Attack::attack values
	explicit shieldbash();
	int bash(bool);
};
}

#endif
