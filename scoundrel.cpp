#include <iostream>
#include "raylib.h"
#include "Deck.h"
#include "Button.h"
#include "Game.h"



int main() {

	// ====================================
	// *      SET DEFAULT PARAMETERS      *
	// ====================================

	// Main draw button parameters
	Vector2 buttonSize = { 100.0f, 100.0f };
	Vector2 buttonPos = { 600.0f, 500.0f };
	ButtonStyle drawButtonStyle = { BLACK, ORANGE, GREEN };

	
	// Set window dimensions
	const int screenWidth = 1280;
	const int screenHeight = 720;


	// Initializes main game object
	Game game;




	// Window Initialization
	InitWindow(screenWidth, screenHeight, "Scoundrel");
	SetTargetFPS(240);
	HideCursor();


	// Main game loop
	while (!WindowShouldClose()) {

	// ====================================
	// *              UPDATE			  *
	// ====================================

		game.Update();

	// ====================================
	// *               DRAW				  *
	// ====================================

		BeginDrawing();
		ClearBackground(DARKGRAY);
		game.Draw(); // Draws main game elements

		// ==== MOUSE POS DEBUG ====
		Vector2 mp = GetMousePosition();
		int crossSize = 10; // Crosshair length
		DrawLine(mp.x - crossSize, mp.y, mp.x + crossSize, mp.y, RAYWHITE); // Draws a crosshair at 
		DrawLine(mp.x, mp.y - crossSize, mp.x, mp.y + crossSize, RAYWHITE); // current mouse position
		DrawText(TextFormat("(%.0f, %.0f)", mp.x, mp.y), mp.x + 12, mp.y - 12, 20, BLACK); // Displays mouse coordinates


		EndDrawing();
	}

	CloseWindow();
	return 0;
}



/* ===== Old Init, Draw, And Update Code =====


	//deck deck; //main deck of cards remaining
	//std::string deckSize = deck.remaining();

	// Creates main draw button and assigns functionality to onClick event
	//Button myButton(buttonPos, buttonSize, drawButtonStyle);
	//myButton.onClick = [&]() {
	//	if (currentPhase != GamePhase::WAITING_FOR_DRAW) return; // cancels event when button not active (wrong phase)
	//	if (cardRow.size() < 4) cardRow.push_back(deck.draw_card()); //draws card if less than 4 cards in row
	//	if (cardRow.size() >= 4) currentPhase = GamePhase::CARD_DRAWN; //moves to next phase when 4 cards drawn
	//	deckSize = deck.remaining();
	//	};
 
	card drawnCard(0, 0); //placeholder for drawn card
	
	std::vector<card> cardRow; //currently active hands in "room"




		mousePoint = GetMousePosition();

		myButton.UpdateButtonState(mousePoint); // Checks if button is being hovered or clicked



		BeginDrawing();
		ClearBackground(DARKGRAY);

		DrawText(TextFormat("Currently %s cards left in deck.", deckSize.c_str()), 500, 450, 20, BLACK);

		// Draws a card for each card in the row
		// then positions them with spacing equal
		// to the current index * a spacing value
		if (currentPhase == GamePhase::CARD_DRAWN){
			for (size_t i = 0; i < cardRow.size(); i++) {
				Vector2 cardPos = { cardStartPos.x + i * cardSpacing, cardStartPos.y };
				cardRow[i].DrawCardImage(cardPos, cardSize);
			}

		}


		if (currentPhase == GamePhase::WAITING_FOR_DRAW) myButton.DrawButton("Draw"); // Shows "draw" button when gamestate = waiting for draw


		*/