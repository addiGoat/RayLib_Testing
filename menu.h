#pragma once
#include <string>
#include "raylib.h"
#include "txtloader.h"
#include "button.h"

enum class ProgramState {
	MAIN_MENU,
	IN_GAME,
	RESETTING
};



class Menu {
public: 
	Menu();
	bool playRequested = false;
	bool displayRules = false;

	Vector2 playButtonPos = { 350.0f, 200.0f };
	Vector2 playButtonSize = { 600.0f, 100.0f };
	float buttonSpacing = 25.0f;

	Button playButton;
	Button rulesButton;
	Button exitButton;
	Button backButton;

	ProgramState currentState = ProgramState::MAIN_MENU;

	bool PlayRequested();


	void UpdateMenu();
	void DrawMenu();
	void DrawRules();

	void MenuReset();

	bool WantsQuit() const;

	static void DrawRulesPanel(const std::vector<std::string>& lines, Rectangle panel, float scrollY);


private:
	std::vector<std::string> rulesLines;
	float rulesScrollY = 0.0f;

	bool wantsQuit = false;
};