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
	hasDrawnCard = false;
	deckSize = mainDeck.remaining();


	// Assign functionality to draw button's onClick event
	drawButton.onClick = [&]() {
		if (currentPhase != GamePhase::WAITING_FOR_DRAW) return; // cancels event when button not active (wrong phase)
		// Implement card drawing logic here
		// e.g., if (cardRow.size() < 4) cardRow.push_back(deck.draw_card());
		// if (cardRow.size() >= 4) currentPhase = GamePhase::CARD_DRAWN;

		drawnCard = mainDeck.draw_card(); // Draw a card from the main deck
		hasDrawnCard = true;
		deckSize = mainDeck.remaining();
		currentPhase = GamePhase::CARD_DRAWN; // Placeholder action to change game phase
		};
}

void Game::Update() {
	Vector2 mousePos = GetMousePosition();
	drawButton.UpdateButtonState(mousePos);
}	

void Game::Draw() {

	DrawText(TextFormat("Currently %i cards left in deck.", (int)deckSize), 500, 450, 20, BLACK);

	if (currentPhase == GamePhase::WAITING_FOR_DRAW) {
		drawButton.DrawButton("Draw Card");
	}

	if (currentPhase == GamePhase::CARD_DRAWN && hasDrawnCard) {
		// Draw the drawn card at a specified positionNope
		Vector2 cardPos = { 590.0f, 200.0f }; // Centered position for drawn card
		Vector2 cardSize = { 100.0f, 150.0f };
		drawnCard.DrawCardImage(cardPos, cardSize, drawButtonColor);
	}
}	