#pragma once
#include "GameState.h"

class StateMachineExampleGame;

class WinState : public GameState
{
	StateMachineExampleGame* m_pOwner;

public:
	WinState(StateMachineExampleGame* pOwner);
	~WinState() = default;

	virtual GameStateType GetType() override { return GameStateType::Win; }
	virtual void Draw() override;
	virtual void Update() override;
};
