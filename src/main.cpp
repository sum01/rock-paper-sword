#include <iostream>
#include <stdexcept>
// Used to get a random move for the enemy
#include <random>
// Used to create a player and enemy
#include "entity.hpp"

// Avoid magic numbers by using an enum
enum Atk_types {sword, fireball, shieldbash};

// The logic handler for an Entity to fight one another
void fight_target(Entity::entity *target, Atk_types target_chose, Entity::entity *attacker, Atk_types attacker_chose) {
	// Whether they blocked or not
	const bool tar_used_shield = (target_chose == shieldbash) ? true : false;

	// Holds actual dmg done
	int dmg_done = 0;
	// Holds potential max dmg (or 0 for fireball)
	int base_dmg = 0;
	// The used attack
	std::string what_atk_happened = "";

	if (attacker_chose == sword) {
		// Calc the dmg done by the swing
		dmg_done = attacker->swing(tar_used_shield);
		// Calc the ublocked dmg
		base_dmg = attacker->swing(false);
		// Tell them what happened
		what_atk_happened = "sword";
	} else if (attacker_chose == fireball) {
		// Calc the dmg done by the swing
		dmg_done = attacker->cast();
		// Tell them what happened
		what_atk_happened = "fireball";
	} else if (attacker_chose == shieldbash) {
		// Use shield bash to reduce hp
		dmg_done = attacker->bash(tar_used_shield);
		// Calc the unblocked dmg
		base_dmg = attacker->bash(false);
		what_atk_happened = "shield bash";
	} else {
		std::runtime_error("Invalid move");
		return;
	}

	target->reduce_hp(dmg_done);

	// Shows absorbed dmg
	std::string any_absorbed = "";
	// Check the unblocked dmg (always 0 for fireball)
	if (base_dmg > dmg_done) {
		// If it was blocked, tell how much was absorbed
		any_absorbed = " (" + std::to_string(base_dmg - dmg_done) + " blocked)";
	}

	// Tell them what happened
	std::cout << attacker->get_name() << " used " << what_atk_happened << ", hit " << target->get_name() << " for " << dmg_done << " dmg." << any_absorbed << std::endl;

	// After reducing its hp, print the new hp
	target->print_hp();
}

// Returns a valid move for use
Atk_types get_player_move() {
	int chosen_move_raw = 0;
	// Get a valid move from player
	while (chosen_move_raw < 1 || chosen_move_raw > 3) {
		std::cout << "Choose a move:\n1 = Swing sword\n2 = Cast fireball\n3 = Shield bash" << std::endl;
		std::cin >> chosen_move_raw;
	}
	std::cout << std::endl;
	// Cast the move into an enum so we can use words to describe what we're doing
	// -1 because enum's are zero-based, but we took in 1-based input for ease of playing
	return static_cast<Atk_types>(chosen_move_raw - 1);
}

bool found_winner(Entity::entity *e1, Entity::entity *e2) {
	// Check for a winner
	if (e1->get_hp() == 0 && e2->get_hp() > 0) {
		std::cout << e2->get_name() << " wins!";
	} else if (e1->get_hp() == 0 && e2->get_hp() == 0) {
		std::cout << "It was a tie!";
	} else {
		return false;
	}

	// We didn't print endl above so we can do game over here.
	std::cout << " Game over." << std::endl;

	return true;
}

int main() {
	// A true/false to start playing
	char keep_playing = 'y';
	// Create our player and enemy
	Entity::entity player("Player");
	Entity::entity enemy("Enemy");

	// For generating random numbers | credit https://stackoverflow.com/a/7560564
	// Get a random num based on a hardware device..
	// Seed the number generator with the random hardware number
	std::mt19937 rng;
	rng.seed(std::random_device()());
	// Defines the range to use (zero-based since enum is too)
	std::uniform_int_distribution<std::mt19937::result_type> rng_distr(0, 2);

	// Define chosen moves outside the loop
	Atk_types enemy_atk;
	Atk_types player_atk;

	std::cout << "Starting Rock Paper Sword!\n" << std::endl;

	// Our gamestate loop
	while (keep_playing == 'y') {
		// Get the players move
		player_atk = get_player_move();

		// Get the enemies random move (is zero-based, no need to minus)
		enemy_atk = static_cast<Atk_types>(rng_distr(rng));

		// Pass by ref so we can change their vals in fight_target()
		// First attack enemy
		fight_target(&enemy, enemy_atk, &player, player_atk);
		// Then attack player with enemy's random move
		fight_target(&player, player_atk, &enemy, enemy_atk);

		if (enemy.get_hp() == 0 || player.get_hp() == 0) {
			// Linebreak after finishing move
			std::cout << std::endl;
			// If player didn't win, and no tie, flip the call
			if (!found_winner(&enemy, &player) && !found_winner(&player, &enemy)) {
				std::runtime_error("Something went wrong, no winner/tie.");
				return 1;
			} else {
				// Check if they want to keep playing
				do {
					std::cout << "Do you want to keep playing? [y/n]" << std::endl;
					std::cin >> keep_playing;
					// Allow upper-case, just lower here
					keep_playing = std::tolower(keep_playing);
				} while (keep_playing != 'y' && keep_playing != 'n');
				// Reset hp if we're going to keep playing
				if (keep_playing == 'y') {
					player.full_hp();
					enemy.full_hp();
					// Send a newline to break between games
					std::cout << "\nStarting a new round.\n" << std::endl;
				}
			}
		} else {
			// Newline between choosing attacks.
			std::cout << std::endl;
		}
	}

	std::cout << "Closing the game." << std::endl;

	return 0;
}
