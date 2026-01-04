#include "Deck.h"

void deck::generate_type(int s) {
	for (int currentRank = 0; currentRank <= 12; currentRank++) {
		main_deck.emplace_back(currentRank, s);
	}
}

deck::deck() {
	std::random_device rd;
	gen = std::mt19937(rd());

	for (int typeInt = 0; typeInt <= 3; typeInt++) {
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
