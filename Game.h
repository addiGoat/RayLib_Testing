#pragma once
#include "Deck.h"
#include "Card.h"
#include "Button.h"

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
	Color drawButtonColor = SKYBLUE;

	size_t deckSize;

	deck mainDeck;
	card drawnCard;
	bool hasDrawnCard;
};

