#pragma once
#include <functional> // for std::function
#include "raylib.h"

struct ButtonStyle {
	Color idleColor;
	Color hoverColor;
	Color pressedColor;
};


class Button {
public:
	Rectangle buttonBounds; //Rectangle defining the button's position and size
	int buttonState; // 0 = normal, 1 = hover, 2 = pressed
	Color buttonColor; // Current chosen color of the button
	ButtonStyle style; // Style struct containing colors for different states
	std::function<void()> onClick; // Callback function for button click action

	Button(Vector2 pos, Vector2 size, ButtonStyle s);

	void UpdateButtonState(Vector2 mousePos);
	void DrawButton(const char* buttonText);

};

