#pragma once
#include <string>
#include "raylib.h"

#define CARD_COLOR_IDLE SKYBLUE
#define CARD_COLOR_HOVER YELLOW

enum Type { MONSTER, POTION, WEAPON };

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

