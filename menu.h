#pragma once
#include "raylib.h"
#include "button.h"

enum class ProgramState {
	MAIN_MENU,
	RULES_MENU,
	IN_GAME,
	RESETTING
};

class Menu {
public: 
	Menu();
	bool playRequested = false;

	Vector2 playButtonPos = { 350.0f, 200.0f };
	Vector2 playButtonSize = { 600.0f, 100.0f };
	float buttonSpacing = 20.0f;

	Button playButton;
	Button rulesButton;
	Button exitButton;
	Button backButton;

	ProgramState currentState = ProgramState::MAIN_MENU;
	
	int hoveredButton = 0;

	bool PlayRequested();


	void UpdateMenu();
	void DrawMenu();
	void MenuReset();

	bool WantsQuit() const;



private:


	bool wantsQuit = false;
};