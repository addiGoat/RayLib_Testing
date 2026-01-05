#pragma once
#include <optional>
#include "Deck.h"
#include "Card.h"
#include "Button.h"
#include "player.h"


// Default card parameters
const Vector2 cardSize = { 100.0f, 150.0f };
const Vector2 cardStartPos = { 430.0f, 100.0f };
const float cardSpacing = 120.0f; // Spacing between drawn cards

const Vector2 resetButtonSize = { 400.0f, 100.0f };
const Vector2 resetButtonPos = { 450.0f, 300.0f };

enum class GamePhase {
	RAN_LAST_ROOM,
	CLEARING_ROOM,
	RESOLVING_ACTION,
	FULL_ROOM
};

enum class GameState {
	PLAYING,
	GAME_OVER,
	VICTORY
};


class Game {
public:
	Game();

	void Update();
	void Draw();

	bool WantsRestart() const;
	bool WantsQuit() const;
	

private:
	GamePhase currentPhase;
	GameState currentState;

	Button runButton;
	Button resetButton;

	bool wantsQuit;
	bool wantsRestart;
	

	void FillRowToMax();

	Color cardColor = CARD_COLOR_IDLE;

	size_t deckSize;

	deck mainDeck;

	Player player;

	void InteractWithCard(size_t index);

	int hoveredCardIndex = -1;

	static constexpr size_t maxRowSize = 4;
	std::array<std::optional<card>, maxRowSize> cardSlots;

	void RunFromRoom();
	
	

	static Color GetCardColor(Type t) {
		switch (t) {
		case MONSTER: return RED;
		case POTION: return GREEN;
		case WEAPON: return BLUE;
		default: return GRAY;
		}
	}
};

