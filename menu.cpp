#include "menu.h"

Menu::Menu():
	playButton(
		playButtonPos,
		playButtonSize,
		ButtonStyle{ BLACK, ORANGE, GREEN }
	),
	rulesButton (
		{ playButtonPos.x, playButtonPos.y },
		playButtonSize,
		ButtonStyle{ BLACK, ORANGE, GREEN }
	),
	exitButton(
		playButtonPos,
		playButtonSize,
		ButtonStyle{ BLACK, ORANGE, GREEN }
	),
	backButton(
		playButtonPos,
		playButtonSize,
		ButtonStyle{ BLACK, ORANGE, GREEN }
	)
{
	bool playRequested = false;

	playButton.onClick = [&]() {
		playRequested = true;
		currentState = ProgramState::IN_GAME;
		};

	

}


void Menu::UpdateMenu() {
	Vector2 mousePos = GetMousePosition();
	
	switch (currentState) {
	case ProgramState::MAIN_MENU:
		playButton.UpdateButtonState(mousePos);

		break;
	case ProgramState::RULES_MENU:

		break;
	}


	if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) wantsQuit = true;
}

void Menu::DrawMenu() {

	switch (currentState) {

		// Print main menu state
	case ProgramState::MAIN_MENU:
		playButton.DrawButton("Play Game", 50);
		DrawText("Scoundrel", 390, 40, 100, BLACK);
		break;

		// Print rule menu state
	case ProgramState::RULES_MENU:
		DrawText("rules menu", 500, 500, 100, BLACK);
		break;
	}
}

bool Menu::WantsQuit() const {
	return wantsQuit;
}

void Menu::MenuReset() {
	playRequested = false;
	currentState = ProgramState::MAIN_MENU;
}