#pragma once
#include "Deck.h"
#include "Card.h"
#include "Button.h"

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

	Color cardColor = SKYBLUE;

	size_t deckSize;

	deck mainDeck;

	void InteractWithCard(size_t index);


	std::vector<card> cardRow;
	const size_t maxRowSize = 4;
};

