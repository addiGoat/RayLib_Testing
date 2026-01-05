#pragma once
#include <string>
#include "raylib.h"

enum Type { MONSTER, POTION, WEAPON, PLACEHOLDER };

class card
{
public:
	card(); // Default constructor
	card(int r, int s);

	const char* type_to_string(Type t);

	void DrawCardImage(Vector2 pos, Vector2 size, Color color);
	


	int get_rank() const;
	Type get_type() const;

private:
	int cardRank;
	Type cardType;

	void print_info() const;
};

