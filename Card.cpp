#include "Card.h"
#include <iostream>

// Converts card type enum to string representation
std::string card::type_to_string(Type s) { 
	switch (s) {
	case MONSTER: return "Monster";
	case WEAPON: return "Weapon";
	case POTION: return "Potion";
	case PLACEHOLDER: return "oopies";
	default: return "INVALID";

	} 
}

// Constructor
card::card(int r, int s) {
	cardRank = r;
	cardType = static_cast<Type>(s);
}

// Default constructor for no input
card::card() {
	cardRank = 0;
	cardType = PLACEHOLDER;
}

int card::get_rank() const {
	return cardRank + 1;
}

Type card::get_type() const {
	return cardType;
}

void card::DrawCardImage(Vector2 pos, Vector2 size, Color color) {
	DrawRectangleV(pos, size, color); // Draw card background
	DrawText(type_to_string(cardType).c_str(), pos.x + 10, pos.y + 10, 20, BLACK); // Draw card type
	DrawText(TextFormat("Level %i", cardRank + 1), pos.x + 10, pos.y + 40, 20, BLACK); // Draw card rank

}


// Console Debugging. Redundant, but possibly useful.
void card::print_info() const {
	std::cout << "A level " << cardRank << " " << cardType << "!\n";
}