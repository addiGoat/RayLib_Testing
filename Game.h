#pragma once
#include <optional>
#include "Deck.h"
#include "Card.h"
#include "Button.h"
#include "player.h"
#include <array>

// Default card parameters
const Vector2 cardSize = { 100.0f, 150.0f };
const Vector2 cardStartPos = { 430.0f, 100.0f };
const float cardSpacing = 120.0f; // Spacing between drawn cards

enum class GamePhase {
	WAITING_FOR_DRAW,
	CARD_DRAWN,
	RESOLVING_CARD
};

class Game {
public:
	Game();

	void Update();
	void Draw();

private:
	GamePhase currentPhase;
	Button drawButton;

	void FillRowToMax();

	Color cardColor = CARD_COLOR_IDLE;

	size_t deckSize;

	deck mainDeck;

	void InteractWithCard(size_t index);

	int hoveredCardIndex = -1;


	std::vector<card> cardRow;
	

	static constexpr size_t maxRowSize = 4;
	std::array<std::optional<card>, maxRowSize> cardSlots;
	
	

	static Color GetCardColor(Type t) {
		switch (t) {
		case MONSTER: return RED;
		case POTION: return GREEN;
		case WEAPON: return BLUE;
		default: return GRAY;
		}
	}
};

