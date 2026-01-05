#include "Deck.h"

void deck::generate_type(int s) {
	
	if (s == 0) {
		for (int t = 0; t <= 1; t++) {
			for (int i = 0; i <= 12; i++) {
				main_deck.emplace_back(i, s); // Monster cards
			}
		}
	}
	else if (s == 1) { 
		for (int i = 0; i <= 8; i++) {
			main_deck.emplace_back(i, s); // Potion cards
		}
	}
	else if (s == 2){
		for (int i = 0; i <= 8; i++) {
			main_deck.emplace_back(i, s); // Weapon cards
		}
	}
}

deck::deck() {
	std::random_device rd;
	gen = std::mt19937(rd());

	for (int typeInt = 0; typeInt <= 2; typeInt++) {
		generate_type(typeInt);
	}

	shuffle();
}

void deck::shuffle() {
	std::shuffle(main_deck.begin(), main_deck.end(), gen);
}

card deck::draw_card() {
	if (main_deck.empty()) {
		throw std::runtime_error("Can't draw card from an empty deck!");
	}
	else {

	}
	card drawnCard = main_deck.back();
	main_deck.pop_back();
	discard_deck.push_back(drawnCard);

	return drawnCard;
}

size_t deck::remaining() const {
	size_t remaining = main_deck.size();
	return remaining;
}
size_t deck::discards() const {
	return discard_deck.size();
}
