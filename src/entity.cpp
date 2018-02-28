#include "entity.hpp"
#include <string>
#include <iostream>

// Name it upon initialization
// Always either "Player" or "Enemy"
Entity::entity::entity(std::string named) {
	this->name = named;
	// Make sure they start with full hp
	this->full_hp();
}

// Fill/reset hp
void Entity::entity::full_hp() {
	this->hp = 10;
}

void Entity::entity::reduce_hp(int reduce_by) {
	this->hp -= reduce_by;
	// Safety check to never fall below 0
	// NOTE: Maybe allow negatives & resolve ties by overkill?
	if (this->hp < 0) {
		this->hp = 0;
	}
}

std::string Entity::entity::get_name() {
	return this->name;
}

int Entity::entity::get_hp() {
	return this->hp;
}

void Entity::entity::print_hp() {
	std::cout << this->get_name() << " has " << this->get_hp() << " hp." << std::endl;
}
