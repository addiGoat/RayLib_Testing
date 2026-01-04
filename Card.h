#pragma once
#include <string>
#include "raylib.h"

enum Type { MONSTER, POTION, WEAPON, PLACEHOLDER };

class card
{
public:
	card(int r, int s);
	
	void print_info() const;

	int get_rank();
	Type get_type();

	std::string type_to_string(Type s);

	void DrawCardImage(Vector2 pos, Vector2 size);

private:
	int cardRank;
	Type cardType;
};

