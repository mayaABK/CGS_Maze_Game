#pragma once
#include "GameState.h"

class StateMachineExampleGame;

class SettingsState : public GameState
{
	StateMachineExampleGame* m_pOwner;

public:
	SettingsState(StateMachineExampleGame* pOwner);
	~SettingsState() = default;

	virtual GameStateType GetType() override { return GameStateType::Settings; }
	virtual void Draw() override;
	virtual void Update() override;
};
