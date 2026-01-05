#include "Card.h"
#include <iostream>

// Converts card type enum to string representation
const char* card::type_to_string(Type t) { 
	switch (t) {
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
	
	// Draw card background
	DrawRectangleV(pos, size, color);

	// ========== Type text at top ==========
	int typeFontSize = 22;
	
	const char* typeText = type_to_string(cardType);

	int typeTextW = MeasureText(typeText, typeFontSize);

	float cardCenterX = pos.x + size.x * 0.5f;
	float cardBottomY = pos.y + size.y;

	float typeTextX = cardCenterX - typeTextW * 0.5f;
	float typeTextY = cardBottomY - typeFontSize - 10.0f;
	
	DrawText(typeText, (int)typeTextX, (int)typeTextY, typeFontSize, BLACK); // Draw card type
	
	

	// ========== Rank text at center ==========

	int rankFontSize = 72;
	const char* rankText = TextFormat("%i", cardRank + 1);
	
	int textW = MeasureText(rankText, rankFontSize);

	float centerX = pos.x + size.x * 0.5f;
	float centerY = pos.y + size.y * 0.5f;

	float textX = centerX - textW * 0.5f;
	float textY = centerY - rankFontSize * 0.5f;


	DrawText(rankText, (int)textX, (int)textY, rankFontSize, BLACK); // Draw card rank

}


// Console Debugging. Redundant, but possibly useful.
void card::print_info() const {
	std::cout << "A level " << cardRank << " " << cardType << "!\n";
}