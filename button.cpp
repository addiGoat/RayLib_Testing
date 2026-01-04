#include "Button.h"

Button::Button(Vector2 pos, Vector2 size, ButtonStyle s) {
	buttonBounds = { pos.x, pos.y, size.x, size.y };
	style = s;
	buttonState = 0;
	buttonColor = style.idleColor;
}

void Button::UpdateButtonState(Vector2 mousePos){
	if (CheckCollisionPointRec(mousePos, buttonBounds)) {
		buttonState = 1; // Hover
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			buttonState = 2; // Pressed
		}
		if (onClick && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) onClick(); // Trigger click action
	}
	else {
		buttonState = 0; // Idle
	}

	// Update button color based on state
	switch (buttonState) {
	case 0: buttonColor = style.idleColor; break;
	case 1: buttonColor = style.hoverColor; break;
	case 2: buttonColor = style.pressedColor; break;
	}
}

void Button::DrawButton(const char* buttonText) {
	DrawRectangleRec(buttonBounds, buttonColor);
	DrawText(buttonText, (float)buttonBounds.x + 10, (float)buttonBounds.y + 10, 20, WHITE);
}