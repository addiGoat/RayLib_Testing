#include <iostream>
#include "raylib.h"
#include "Deck.h"
#include "Button.h"

#define DRAW_BUTTON_WIDTH 100
#define DRAW_BUTTON_HEIGHT 100
#define DRAW_BUTTON_X 600
#define DRAW_BUTTON_Y 500

enum class GamePhase {
	WAITING_FOR_DRAW,
	CARD_DRAWN,
	RESOLVING_CARD
};


int main() {

	const int screenWidth = 1280;
	const int screenHeight = 720;

	Vector2 buttonSize = { DRAW_BUTTON_WIDTH, DRAW_BUTTON_HEIGHT };
	Vector2 buttonPos = { DRAW_BUTTON_X, DRAW_BUTTON_Y };
	ButtonStyle drawButtonStyle = { BLACK, ORANGE, GREEN };

	Vector2 cardSize = { 100.0f, 150.0f };
	Vector2 cardStartPos = { 430.0f, 100.0f };
	float cardSpacing = 120.0f;

	
	deck deck; //main deck of cards remaining
	std::string deckSize = deck.remaining();



	card drawnCard(0, 0);
	
	std::vector<card> cardRow; //currently active hands in "room"
	
	GamePhase currentPhase = GamePhase::WAITING_FOR_DRAW; //sets the current phase of the game
	

	// Creates main draw button and assigns functionality to onClick event
	Button myButton(buttonPos, buttonSize, drawButtonStyle);
	myButton.onClick = [&]() {
		if (currentPhase != GamePhase::WAITING_FOR_DRAW) return; // cancels event when button not active (wrong phase)
		if (cardRow.size() < 4) cardRow.push_back(deck.draw_card()); //draws card if less than 4 cards in row
		if (cardRow.size() >= 4) currentPhase = GamePhase::CARD_DRAWN; //moves to next phase when 4 cards drawn
		deckSize = deck.remaining();
		};

	Vector2 mousePoint = { 0.0f, 0.0f };

	

	InitWindow(screenWidth, screenHeight, "Scoundrel");
	SetTargetFPS(240);
	HideCursor();


	// Main game loop
	while (!WindowShouldClose()) {


		// ====================================
		// =              UPDATE			  =
		// ====================================

		mousePoint = GetMousePosition();

		myButton.UpdateButtonState(mousePoint); // Checks if button is being hovered or clicked



		// ====================================
		// =               DRAW				  =
		// ====================================
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