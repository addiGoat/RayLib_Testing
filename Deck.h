#pragma once 
#include <vector>
#include <random>
#include <algorithm>
#include "Card.h"


class deck
{
private:
	std::vector<card> main_deck;
	std::vector<card> discard_deck;

	std::mt19937 gen;

	void generate_type(int s);

public:
	deck();

	void shuffle();

	card draw_card();
	std::string remaining() const;
	size_t discards() const;
};