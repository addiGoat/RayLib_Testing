#include "Game.h"
#include "raylib.h"

Game::Game() 
	: drawButton(
		Vector2{ 600.0f, 500.0f },
		Vector2{ 100.0f, 100.0f },
		ButtonStyle{ BLACK, ORANGE, GREEN }
	)	// Initialize Draw Cards Button with position, size, and style
{
	currentPhase = GamePhase::WAITING_FOR_DRAW;
	deckSize = mainDeck.remaining();


	// Assign functionality to draw button's onClick event
	drawButton.onClick = [&]() {

		switch (currentPhase) {

		// Setup draw card action
		case GamePhase::WAITING_FOR_DRAW:
			if (deckSize == 0) return; // Prevent drawing if deck is empty
			if (cardRow.size() < maxRowSize) {
				cardRow.push_back(mainDeck.draw_card());
				deckSize = mainDeck.remaining();
			}
			if (cardRow.size() >= maxRowSize) currentPhase = GamePhase::CARD_DRAWN;
			break;

		// Setup discard action
		case GamePhase::CARD_DRAWN:
			cardRow.clear(); // Clear the drawn cards
			currentPhase = GamePhase::WAITING_FOR_DRAW; // Reset to waiting for draw phase
			break;

		default: return; // Default case to handle unexpected phases
		}
		};

}

void Game::Update() {
	Vector2 mousePos = GetMousePosition();
	drawButton.UpdateButtonState(mousePos);
}	

void Game::Draw() {

	DrawText(TextFormat("Currently %i cards left in deck.", (int)deckSize), 500, 450, 20, BLACK);

	switch (currentPhase) {
	case GamePhase::WAITING_FOR_DRAW:
		drawButton.DrawButton("Draw");
		if (cardRow.size() > 0) {
			for (size_t i = 0; i < cardRow.size(); i++) {
				Vector2 cardPos = { cardStartPos.x + i * cardSpacing, cardStartPos.y };
				cardRow[i].DrawCardImage(cardPos, cardSize, cardColor);
			}
		}
		break;

	case GamePhase::CARD_DRAWN:
		drawButton.DrawButton("Reset");
		if (cardRow.size() > 0) {
			for (size_t i = 0; i < cardRow.size(); i++) {
				Vector2 cardPos = { cardStartPos.x + i * cardSpacing, cardStartPos.y };
				cardRow[i].DrawCardImage(cardPos, cardSize, cardColor);
			}
		}
		
		break;

	default: return; // Default case to handle unexpected phases
	}
}	