#pragma once
#include "GameState.h"

class StateMachineExampleGame;

class MainMenuState : public GameState
{
	StateMachineExampleGame* m_pOwner;

public:
	MainMenuState(StateMachineExampleGame* pOwner);
	~MainMenuState() = default;

	virtual GameStateType GetType() override { return GameStateType::MainMenu; }
	virtual void Update() override;
	virtual void Draw() override;
	bool ShouldQuitGame() { return m_shouldQuit; }
private:
	bool m_shouldQuit;
};

