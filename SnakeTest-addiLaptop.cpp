#include "raylib.h"
#define CUBE_SIZE 50


int main() {

	// Initialization
	//---------------------------
	const int screenWidth = 1600;
	const int screenHeight = 900;

	// for screen boundaries
	const int boundRight = screenWidth - CUBE_SIZE;
	const int boundDown = screenHeight - CUBE_SIZE;



	Vector2 rectanglePos{ screenWidth / 2, screenHeight / 2 };
	Vector2 rectangleSize{ CUBE_SIZE, CUBE_SIZE };

	float velocity = (float)CUBE_SIZE/5.0f;

	bool closeWindowRequested = false;
	bool closeWindow = false;

	SetExitKey(KEY_NULL);

	InitWindow(screenWidth, screenHeight, "Main Window");

	SetTargetFPS(60);

	while (!closeWindow) {

		// Update
		//-------------------------------------------------------------------------


		if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) closeWindowRequested = true;


		if (closeWindowRequested) {
			if (IsKeyPressed(KEY_N)) closeWindowRequested = false;
			else if (IsKeyPressed(KEY_Y)) closeWindow = true;
		}
		// Movement input
		if (IsKeyDown(KEY_RIGHT)) rectanglePos.x += velocity;
		if (IsKeyDown(KEY_UP)) rectanglePos.y -= velocity;
		if (IsKeyDown(KEY_LEFT)) rectanglePos.x -= velocity;
		if (IsKeyDown(KEY_DOWN)) rectanglePos.y += velocity;

		// Stops player from moving off screen
		if (rectanglePos.x > boundRight) rectanglePos.x = boundRight;
		if (rectanglePos.y > boundDown) rectanglePos.y = boundDown;
		if (rectanglePos.x < 0) rectanglePos.x = 0;
		if (rectanglePos.y < 0) rectanglePos.y = 0;



		// Draw
		//------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		if (closeWindowRequested) {
			DrawRectangle(0, (float)screenHeight/3.0f, screenWidth, (float)screenHeight/3.0f, BLACK);
			DrawText("Are you sure you want to leave? (y/n)", 100, (screenHeight / 2) - 15, 30, WHITE);
		}
		else if (!closeWindowRequested) {
			DrawRectangleV(rectanglePos, rectangleSize, BLACK);
		}


		EndDrawing();
	}

	CloseWindow;

	return 0;
}