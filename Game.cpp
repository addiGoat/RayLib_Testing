#include "Game.h"
#include "raylib.h" 
#include <iostream>


// ====================================
// *            CONSTRUCTOR           *
// ====================================
Game::Game():
	runButton(
		Vector2{ 930.0f, 140.0f },
		Vector2{ 200.0f, 100.0f },
		ButtonStyle{ BLACK, ORANGE, GREEN }
	),	// Initialize Draw Cards Button with position, size, and style
	resetButton(
		resetButtonPos,
		resetButtonSize,
		ButtonStyle{ BLACK, ORANGE, GREEN } 
	)
{
	wantsRestart = false;
	wantsQuit = false;
	currentPhase = GamePhase::FULL_ROOM;
	currentState = GameState::PLAYING;
	deckSize = mainDeck.remaining();
	FillRowToMax();


	// Assign functionality to draw button's onClick event
	runButton.onClick = [&]() {

		switch (currentPhase) {
		case GamePhase::FULL_ROOM:
			RunFromRoom();
			currentPhase = GamePhase::RAN_LAST_ROOM; 
			break;

		case GamePhase::RAN_LAST_ROOM:
			 
			break;
		case GamePhase::CLEARING_ROOM:  
			break;


		};

	};

	resetButton.onClick = [&]() {
		if (currentState != GameState::PLAYING) {
			wantsRestart = true;
		}
	};


}

// ====================================
// *              UPDATE			  *
// ====================================
void Game::InteractWithCard(size_t index) {
	
	if (index >= cardSlots.size()) return; // Invalid index
	if (!cardSlots[index].has_value()) return; // No card in this slot
	

	// get_rank returns rank + 2 (a 2-14 value), so no need to add 1 for weapon and monster
	switch (cardSlots[index]->get_type()) {
	case MONSTER: player.Attack(cardSlots[index]->get_rank()); break;
	case WEAPON: player.Equip(cardSlots[index]->get_rank());  break;
	case POTION: player.Heal(cardSlots[index]->get_rank()); break;
	}


	cardSlots[index].reset(); // Remove the card from the slot

	size_t filledSlots = 0;
	for (auto& s : cardSlots) {
		if (s.has_value()) filledSlots++;
	}


	if (player.IsDead()) {
		currentState = GameState::GAME_OVER;
	}
	else if (deckSize == 0 && filledSlots == 0) {
		currentState = GameState::VICTORY;
	}
	else {
		
		currentPhase = GamePhase::CLEARING_ROOM;
		if (filledSlots == 1) FillRowToMax(); // Refill row if all slots are empty

	}
}

void Game::Update() {
	Vector2 mousePos = GetMousePosition();

	switch (currentState) {
	case GameState::PLAYING:
		runButton.UpdateButtonState(mousePos);

		// Handles card interaction bounds
		for (size_t i = 0; i < cardSlots.size(); i++) {
			Vector2 cardPos = { cardStartPos.x + i * cardSpacing, cardStartPos.y };
			Rectangle cardRect = { cardPos.x, cardPos.y, cardSize.x, cardSize.y };

			if (CheckCollisionPointRec(mousePos, cardRect) && cardSlots[i].has_value()) {
				hoveredCardIndex = (int)i;
				if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
					InteractWithCard(hoveredCardIndex);
					hoveredCardIndex = -1; // Reset hovered index after interaction
					break;
				}
				break;
			}
		}
		break;
	case GameState::GAME_OVER:
		resetButton.UpdateButtonState(mousePos);
	}

	hoveredCardIndex = -1;

	if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) wantsQuit = true;

}	

void Game::FillRowToMax() {
	for (size_t i = 0; i < maxRowSize && deckSize > 0; i++) {
		if (!cardSlots[i].has_value()) {
			cardSlots[i] = mainDeck.draw_card();
			deckSize = mainDeck.remaining();
		}
	}

	if (currentPhase == GamePhase::RAN_LAST_ROOM || currentPhase == GamePhase::CLEARING_ROOM) currentPhase = GamePhase::FULL_ROOM;
}



// ====================================
// *               DRAW               *
// ====================================

void Game::Draw() {

	switch (currentState) {
	case GameState::PLAYING:

		DrawText(TextFormat("Currently %i cards left in dungeon.", (int)deckSize), 50, 150, 20, BLACK);
		DrawText(TextFormat("Player HP: %i", player.HP()), 50, 50, 50, BLACK); // Placeholder for player HP display))

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

		// Draw equipped weapon if player has one
		if (player.weaponDamage > 0) {
			player.DrawEquippedWeapon();
		}

		switch (currentPhase) {
			// Displays message to allow running if action valid
		case GamePhase::FULL_ROOM:
			runButton.DrawButton("Run", 50);
			break;

			// Displays message if unable to run
		case GamePhase::RAN_LAST_ROOM:
			runButton.DrawButton("Can't Run", 35);
			DrawText("Can't run twice\nin a row", 930, 75, 30, BLACK);
			break;

		case GamePhase::CLEARING_ROOM:
			runButton.DrawButton("Can't Run", 35);
			DrawText("Can only run\nwith full hand", 930, 75, 30, BLACK);
			break;

		default: return; // Default case to handle unexpected phases
		}

		break;

	case GameState::GAME_OVER: 
		DrawText("YOU DIED", 400, 100, 100, BLACK);
		resetButton.DrawButton("Reset", 50);
		break;
	case GameState::VICTORY:
		DrawText("YOU WON", 400, 100, 100, BLACK);
		resetButton.DrawButton("Reset", 50);
		break;
	}

}	

void Game::RunFromRoom() {
	for (size_t i = 0; i < maxRowSize; i++) {
		if (cardSlots[i].has_value()) {
			mainDeck.PutOnBottom(*cardSlots[i]);
			cardSlots[i].reset();
		}
	}

	deckSize = mainDeck.remaining();
	FillRowToMax();
}

bool Game::WantsRestart() const {
	return wantsRestart;
}

bool Game::WantsQuit() const {
	return wantsQuit;
}