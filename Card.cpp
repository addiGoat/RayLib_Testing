#include "Card.h"
#include <iostream>

std::string card::type_to_string(Type s) {
	switch (s) {
	case MONSTER: return "Monster";
	case WEAPON: return "Weapon";
	case POTION: return "Potion";
	case PLACEHOLDER: return "oopies";
	default: return "INVALID";

	}
}

card::card(int r, int s) {
	cardRank = r;
	cardType = static_cast<Type>(s);
}

void card::print_info() const{
	std::cout << "A level " << cardRank << " " << cardType << "!\n";
}

int card::get_rank() {
	return cardRank + 1;
}

Type card::get_type() {
	return cardType;
}

void card::DrawCardImage(Vector2 pos, Vector2 size) {
	DrawRectangleV(pos, size, LIGHTGRAY);

	DrawText(type_to_string(cardType).c_str(), pos.x + 10, pos.y + 10, 20, BLACK);
	DrawText(TextFormat("Level %i", cardRank + 1), pos.x + 10, pos.y + 40, 20, BLACK);

}