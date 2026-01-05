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


	// Initialize main game object
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