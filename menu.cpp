#include "menu.h"

Menu::Menu():
	playButton(
		playButtonPos,
		playButtonSize,
		ButtonStyle{ BLACK, ORANGE, GREEN }
	),
	rulesButton (
		{ playButtonPos.x, playButtonPos.y + playButtonSize.y + buttonSpacing },
		playButtonSize,
		ButtonStyle{ BLACK, ORANGE, GREEN }
	),
	exitButton(
		{ playButtonPos.x, playButtonPos.y + (playButtonSize.y + buttonSpacing) * 2.0f},
		playButtonSize,
		ButtonStyle{ BLACK, ORANGE, GREEN }
	),
	backButton(
		{ playButtonPos.x, 570.0f },
		playButtonSize,
		ButtonStyle{ BLACK, ORANGE, GREEN }
	)
{
	bool playRequested = false;

	rulesLines = LoadTextFileLines("rules.txt");
	rulesScrollY = 0.0f;

	playButton.onClick = [&]() {
		playRequested = true;
		currentState = ProgramState::RESETTING;
		};

	rulesButton.onClick = [&]() {
		displayRules = true;
		};

	backButton.onClick = [&]() {
		displayRules = false;
		};

	exitButton.onClick = [&]() {
		wantsQuit = true;
		};
	

}


void Menu::UpdateMenu() {
	Vector2 mousePos = GetMousePosition();
	
	switch (currentState) {
	case ProgramState::MAIN_MENU:
		if (displayRules) {
			// Scroll with mouse wheel
			float wheel = GetMouseWheelMove();
			rulesScrollY -= wheel * 30.0f; // invert if you want opposite direction

			if (rulesScrollY < 0.0f) rulesScrollY = 0.0f;

			// Optional: arrow keys
			if (IsKeyDown(KEY_DOWN)) rulesScrollY += 6.0f;
			if (IsKeyDown(KEY_UP))   rulesScrollY -= 6.0f;
			if (rulesScrollY < 0.0f) rulesScrollY = 0.0f;

			backButton.UpdateButtonState(mousePos);
		}
		else {
			playButton.UpdateButtonState(mousePos);
			rulesButton.UpdateButtonState(mousePos);
			exitButton.UpdateButtonState(mousePos);
		}


		break;
	}


	if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) wantsQuit = true;
}

void Menu::DrawMenu() {

	switch (currentState) {

		// Print main menu state
	case ProgramState::MAIN_MENU:
		if (displayRules) {
			backButton.DrawButton("Back to Menu", 50);
			DrawText("Game Rules", 425, 40, 75, BLACK);

			Rectangle panel = { 80, 120, 1120, 430 };
			DrawRulesPanel(rulesLines, panel, rulesScrollY);

			//backButton.DrawButton("Back", 40);
			DrawText("Scroll wheel to read", 80, 620, 22, BLACK); // arrows hint
			break;
	
		}
		else {
			playButton.DrawButton("Play Game", 50);
			rulesButton.DrawButton("Game Rules", 50);
			exitButton.DrawButton("Quit Game", 50);

			DrawText("Scoundrel", 390, 40, 100, BLACK);
		}

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

void Menu::DrawRulesPanel(const std::vector<std::string>& lines, Rectangle panel, float scrollY)
{
	// Panel background
	DrawRectangleRec(panel, RAYWHITE);
	DrawRectangleLinesEx(panel, 2.0f, BLACK);

	BeginScissorMode((int)panel.x, (int)panel.y, (int)panel.width, (int)panel.height);

	float x = panel.x + 16.0f;
	float y = panel.y + 16.0f - scrollY;

	for (const std::string& raw : lines)
	{
		// Basic formatting rules
		int fontSize = 22;
		int indent = 0;
		std::string text = raw;

		if (text.rfind("# ", 0) == 0) { fontSize = 40; text = text.substr(2); }
		else if (text.rfind("## ", 0) == 0) { fontSize = 30; text = text.substr(3); }
		else if (text.rfind("- ", 0) == 0) { fontSize = 22; indent = 20; }

		// Blank lines: add spacing
		if (text.empty())
		{
			y += 14.0f;
			continue;
		}

		DrawText(text.c_str(), (int)(x + indent), (int)y, fontSize, BLACK);
		y += (float)fontSize + 6.0f;
	}

	EndScissorMode();
}
