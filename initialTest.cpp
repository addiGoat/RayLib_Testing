/*#include "raylib.h"

int main()
{

	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "My Window");

	SetExitKey(KEY_NULL);

	bool exitWindowRequested = false;
	bool exitWindow = false;


	int currentFPS = 60;

	Vector2 deltaCircle{ 0, (float)screenHeight / 3.0f };
	Vector2 frameCircle{ 0, (float)screenHeight*(2.0f/3.0f) };

	const float speed = 10.0f;
	const float circleRadius = 32.0f;

	SetTargetFPS(currentFPS);

	while (!exitWindow) {
		// Adjust FPS based on mouse wheel
		float mouseWheel = GetMouseWheelMove(); // Returns float
		if (mouseWheel != 0) {					// Checks if float is not zero
			currentFPS += (int)mouseWheel;		// adds mouseWheel (converted to int) to FPS then adds together
			if (currentFPS < 0) currentFPS = 0; // Stops FPS going lower than 0
			SetTargetFPS(currentFPS);			// Makes the FPS change
		}


		// GetFrameTime() returns the time it took to draw the last frame, in seconds (usually called delta time)
		// Uses the delta time to make the circle look like it's moving at a "consistent" speed regardless of FPS

		// Multiply by 6.0 (an arbitrary value) in order to make the speed
		// visually closer to the other circle (at 60 fps), for comparison
		deltaCircle.x += GetFrameTime() * 6.0f * speed;
		frameCircle.x += 0.1f * speed;

		// If circle x goes off screen (more than x=800) reset back to 0
		if (deltaCircle.x > screenWidth) deltaCircle.x = 0;
		if (frameCircle.x > screenWidth) frameCircle.x = 0;


		// Reset Circles Positions
		if (IsKeyPressed(KEY_R)) {
			deltaCircle.x = 0;
			frameCircle.x = 0;
		}



		if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) exitWindowRequested = true;

		if (exitWindowRequested) {
			if (IsKeyPressed(KEY_Y)) exitWindow = true;
			else if (IsKeyPressed(KEY_N)) exitWindowRequested = false;
		}

		//---------------------------
		// Draw
		//---------------------------
		BeginDrawing();
			ClearBackground(RAYWHITE);
			const char* fpsText = 0;

			if (exitWindowRequested) {
				DrawRectangle(0, 100, screenWidth, 200, BLACK);
				DrawText("You're leaving me? :(", 40, 180, 30, WHITE);
			}
			else if (!exitWindowRequested) {
				
				DrawCircleV(deltaCircle, circleRadius, RED);
				DrawCircleV(frameCircle, circleRadius, RED);


		------------------------------------------------------------------------------------------------------------------------
				if (currentFPS <= 0) fpsText = TextFormat("FPS: Unlimited (%i)", GetFPS());
				else fpsText = TextFormat("FPS: %i (target: %i)", GetFPS(), currentFPS);
				DrawText(fpsText, 10, 10, 20, DARKGRAY);
				DrawText(TextFormat("Frame time: %02.02f ms", GetFrameTime()), 10, 30, 20, DARKGRAY);
				DrawText("Use the scroll wheel to change the fps limit, r to reset", 10, 50, 20, DARKGRAY);
		------------------------------------------------------------------------------------------------------------------------




				DrawText("FUNC: x += GetFrameTime()*speed", 10, 90, 20, RED);
				DrawText("FUNC: x += speed", 10, 240, 20, BLUE);
			}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}*/