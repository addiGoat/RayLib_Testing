#include <iostream>
#include "raylib.h"
#include "Deck.h"
#include "Button.h"

#define DRAW_BUTTON_WIDTH 100
#define DRAW_BUTTON_HEIGHT 100
#define DRAW_BUTTON_X 600
#define DRAW_BUTTON_Y 200

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
	
	bool deckInitialized = false;

	deck deck;
	std::string deckSize = deck.remaining();

	int drawnRank = 0;
	std::string drawnType;
	card drawnCard = card(0, 0);
	
	GamePhase currentPhase = GamePhase::WAITING_FOR_DRAW;
	
	Button myButton(buttonPos, buttonSize, drawButtonStyle);
	myButton.onClick = [&]() {
		if (currentPhase != GamePhase::WAITING_FOR_DRAW) return;

		drawnCard = deck.draw_card();
		drawnRank = drawnCard.get_rank();
		drawnType = drawnCard.type_to_string(drawnCard.get_type());
		deckSize = deck.remaining();
		
		currentPhase = GamePhase::CARD_DRAWN;
		};

	Vector2 mousePoint = { 0.0f, 0.0f };

	

	InitWindow(screenWidth, screenHeight, "Scoundrel");

	SetTargetFPS(60);

	while (!WindowShouldClose()) {


		// Update
	   //----------------------------------------------------------------------------------

		mousePoint = GetMousePosition();
		
		myButton.UpdateButtonState(mousePoint);

		const char* drawnCardText;
		drawnCardText = TextFormat("Drawn card is a level %i %s", drawnRank, drawnType.c_str());

		// Draw
	   //----------------------------------------------------------------------------------------------------
		BeginDrawing();

		
		ClearBackground(RAYWHITE);

		DrawText(deckSize.c_str(), 100, 100, 20, BLACK);
		

		DrawText(drawnCardText, 500, 500, 30, BLACK);
		

		myButton.DrawButton("Draw");



		EndDrawing();
	}

	CloseWindow();
	return 0;
}