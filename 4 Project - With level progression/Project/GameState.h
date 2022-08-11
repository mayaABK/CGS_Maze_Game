#pragma once

enum class GameStateType
{
	Gameplay,
	HighScore,
	Lose,
	MainMenu,
	Settings,
	Win
};

class GameState
{
public:
	virtual ~GameState() {}

	virtual GameStateType GetType() = 0;
	virtual void Enter() {}
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void Exit() {}
};