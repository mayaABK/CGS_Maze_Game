#pragma once
#include "GameState.h"

class StateMachineExampleGame;

class LoseState : public GameState
{
	StateMachineExampleGame* m_pOwner;

public:
	LoseState(StateMachineExampleGame* pOwner);
	~LoseState() = default;

	virtual GameStateType GetType() override { return GameStateType::Lose; }
	virtual void Draw() override;
	virtual void Update() override;
};


