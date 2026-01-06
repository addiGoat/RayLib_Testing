#include <iostream>
#include <optional>
#include "raylib.h"
#include "Deck.h"
#include "Button.h"
#include "Game.h"
#include "menu.h"
#include "txtloader.h"


void DrawMouse(Vector2 mp) {

	DrawTriangle(
		mp,
		{ mp.x, mp.y + 50 },
		{ mp.x + 50, mp.y + 50 },

		WHITE
	);
	DrawRectangle(90, 90, 20, 20, RED);
}


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


	ProgramState currentState = ProgramState::MAIN_MENU;


	// Initialize main game object
	

	bool exitWindow = false;
	bool exitWindowRequested = false;

	SetExitKey(KEY_NULL);


	// Window Initialization
	InitWindow(screenWidth, screenHeight, "Scoundrel");
	SetTargetFPS(240);
	HideCursor();

	Menu mainMenu;

	std::optional<Game> game;


	// Main game loop
	while (!exitWindow) {

		// ====================================
		// *              UPDATE			  *
		// ====================================

		



		switch (currentState) {
		// Handles Updates for the Main Menu
		case ProgramState::MAIN_MENU:
			mainMenu.UpdateMenu();
			currentState = mainMenu.currentState;
			break;

		case ProgramState::IN_GAME:

			
			game->Update();

			// Sets new game object if restart is requested
			if (game->WantsRestart()) {

				game.emplace();
			}

			if (game->WantsQuit()) {
				mainMenu.MenuReset();
				currentState = ProgramState::MAIN_MENU;
			}
			break;
		case ProgramState::RESETTING:
			game.reset();
			game.emplace();
			currentState = ProgramState::IN_GAME;
			break;
		}

		if (mainMenu.WantsQuit()) exitWindow = true;





		if (WindowShouldClose()) exitWindow = true;
		// ====================================
		// *               DRAW				  *
		// ====================================

		BeginDrawing();

		switch (currentState) {
		case ProgramState::MAIN_MENU:

			if (mainMenu.displayRules) ClearBackground({ 11, 12, 69 });
			else {
				ClearBackground({ 69, 25, 11 });
			}
			mainMenu.DrawMenu();
			break;

		case ProgramState::IN_GAME:
			ClearBackground(DARKGRAY);
			game->Draw(); // Draws main game elements
			break;
		case ProgramState::RESETTING:
			ClearBackground(BLACK);
			break;
		}
		
		


		
		// ==== MOUSE POS DEBUG ====
		Vector2 mp = GetMousePosition();
		
		EndMode2D();
		EndMode3D();
		EndTextureMode();
		EndScissorMode();

		DrawMouse(mp);
		//int crossSize = 3; // Crosshair length
		//DrawLine(mp.x - crossSize, mp.y, mp.x + crossSize, mp.y, BLACK); // Draws a crosshair at 
		//DrawLine(mp.x, mp.y - crossSize, mp.x, mp.y + crossSize, BLACK); // current mouse position
		//DrawCircle(mp.x, mp.y, 5, BLACK);
		//Draw
		//DrawText(TextFormat("(%.0f, %.0f)", mp.x, mp.y), mp.x + 12, mp.y - 12, 20, BLACK); // Displays mouse coordinates
		

		EndDrawing();
	}

	CloseWindow();
	return 0;
}