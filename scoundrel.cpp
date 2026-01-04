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

	deck deck;
	std::string deckSize = deck.remaining();



	card drawnCard(0, 0);
	
	std::vector<card> cardRow;
	
	GamePhase currentPhase = GamePhase::WAITING_FOR_DRAW;
	
	Button myButton(buttonPos, buttonSize, drawButtonStyle);
	myButton.onClick = [&]() {
		if (currentPhase != GamePhase::WAITING_FOR_DRAW) return;

		if (cardRow.size() < 4) cardRow.push_back(deck.draw_card());
		
		
		if (cardRow.size() >= 4) currentPhase = GamePhase::CARD_DRAWN;
		deckSize = deck.remaining();
		};

	Vector2 mousePoint = { 0.0f, 0.0f };

	

	InitWindow(screenWidth, screenHeight, "Scoundrel");
	
	HideCursor();

	SetTargetFPS(240);

	while (!WindowShouldClose()) {


		// Update
		//----------------------------------------------------------------------------------

		mousePoint = GetMousePosition();

		myButton.UpdateButtonState(mousePoint);

		//const char* drawnCardText;
		//drawnCardText = TextFormat("Drawn card is a level %i %s", drawnRank, drawnType.c_str());

		// Draw
		//----------------------------------------------------------------------------------------------------
		BeginDrawing();


		ClearBackground(RAYWHITE);

		DrawText(TextFormat("Currently %s cards left in deck.", deckSize.c_str()), 500, 450, 20, BLACK);


		if (currentPhase == GamePhase::CARD_DRAWN){
			//drawnCard.DrawCardImage({ 600.0f, 300.0f }, { 100.0f, 150.0f });

			for (size_t i = 0; i < cardRow.size(); i++) {
				Vector2 cardPos = { cardStartPos.x + i * cardSpacing, cardStartPos.y };
				cardRow[i].DrawCardImage(cardPos, cardSize);
			}
			
		}
		
		if (currentPhase == GamePhase::WAITING_FOR_DRAW) myButton.DrawButton("Draw");


		/*MOUSE POS DEBUG
		Vector2 mousePos = GetMousePosition();
		DrawText(TextFormat("Mouse: %.0f, %.0f", mousePos.x, mousePos.y), 10, 10, 20, BLACK);
		DrawRectangleLines(mousePos.x - 5, mousePos.y - 5, 10, 10, RED);*/

		Vector2 mp = GetMousePosition();
		int crossSize = 10;
		DrawLine(mp.x - crossSize, mp.y, mp.x + crossSize, mp.y, RED);
		DrawLine(mp.x, mp.y - crossSize, mp.x, mp.y + crossSize, RED);
		DrawText(TextFormat("(%.0f, %.0f)", mp.x, mp.y), mp.x + 12, mp.y - 12, 20, BLACK);


		EndDrawing();
	}

	CloseWindow();
	return 0;
}