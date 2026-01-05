#include "Game.h"
#include "raylib.h" 
#include <iostream>


// ====================================
// *            CONSTRUCTOR           *
// ====================================
Game::Game() 
	: drawButton(
		Vector2{ 600.0f, 500.0f },
		Vector2{ 100.0f, 100.0f },
		ButtonStyle{ BLACK, ORANGE, GREEN }
	)	// Initialize Draw Cards Button with position, size, and style
{
	currentPhase = GamePhase::WAITING_FOR_DRAW;
	deckSize = mainDeck.remaining();
	FillRowToMax();


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

// ====================================
// *              UPDATE			  *
// ====================================
void Game::InteractWithCard(size_t index) {
	if (index >= cardSlots.size()) return; // Invalid index
	if (!cardSlots[index].has_value()) return; // No card in this slot

	cardSlots[index].reset(); // Remove the card from the slot

	size_t filledSlots = 0;
	for (auto& s : cardSlots) {
		if (s.has_value()) filledSlots++;
	}

	if (filledSlots == 1) FillRowToMax(); // Refill row if all slots are empty
}

void Game::Update() {
	Vector2 mousePos = GetMousePosition();
	drawButton.UpdateButtonState(mousePos);

	hoveredCardIndex = -1;

	for (size_t i = 0; i < cardSlots.size(); i++) {
		Vector2 cardPos = { cardStartPos.x + i * cardSpacing, cardStartPos.y };
		Rectangle cardRect = { cardPos.x, cardPos.y, cardSize.x, cardSize.y };

		if (CheckCollisionPointRec(mousePos, cardRect) && cardSlots[i].has_value()) {
			hoveredCardIndex = (int)i;
			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
				InteractWithCard(i);
				hoveredCardIndex = -1; // Reset hovered index after interaction
				break;
			} 
			break;
		}
	}
}	

void Game::FillRowToMax() {
	for (size_t i = 0; i < maxRowSize && deckSize > 0; i++) {
		if (!cardSlots[i].has_value()) {
			cardSlots[i] = mainDeck.draw_card();
			deckSize = mainDeck.remaining();
		}
	}
}



// ====================================
// *               DRAW               *
// ====================================

void Game::Draw() {

	DrawText(TextFormat("Currently %i cards left in deck.", (int)deckSize), 500, 450, 20, BLACK);

	for (size_t i = 0; i < maxRowSize; i++) {
		Vector2 cardPos = { cardStartPos.x + i * cardSpacing, cardStartPos.y };

		if (cardSlots[i].has_value()) {
			Color base = GetCardColor(cardSlots[i]->get_type());
			Color currentColor = (hoveredCardIndex == (int)i) ? YELLOW : base;
			cardSlots[i]->DrawCardImage(cardPos, cardSize, currentColor);
		}
		else {
			// Draw empty card slot
			DrawRectangleV(cardPos, cardSize, GRAY);
		}
	}
	
	
	
	//if (cardRow.size() > 0) {
	//	for (size_t i = 0; i < cardRow.size(); i++) {
	//		Vector2 cardPos = { cardStartPos.x + i * cardSpacing, cardStartPos.y };
	//		Color base = GetCardColor(cardRow[i].get_type());
	//		Color currentColor = (hoveredCardIndex == (int)i) ? YELLOW : base;
	//		cardRow[i].DrawCardImage(cardPos, cardSize, currentColor);
	//	}
	//}
	switch (currentPhase) {
		// Draws one card for ever card in row, reads "Draw" on button
	case GamePhase::WAITING_FOR_DRAW:
		drawButton.DrawButton("Draw");
		
		break;
		// Draws all cards when hand is full, reads "Discard" on button
	case GamePhase::CARD_DRAWN:
		drawButton.DrawButton("Discard");
		//if (cardRow.size() > 0) {
		//	for (size_t i = 0; i < cardRow.size(); i++) {
		//		Vector2 cardPos = { cardStartPos.x + i * cardSpacing, cardStartPos.y };
		//		Color base = GetCardColor(cardRow[i].get_type());
		//		Color currentColor = (hoveredCardIndex == (int)i) ? YELLOW : base;
		//		cardRow[i].DrawCardImage(cardPos, cardSize, currentColor);
		//	}
		//}
		
		break;

	default: return; // Default case to handle unexpected phases
	}
}	