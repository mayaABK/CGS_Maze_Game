#pragma once
#include "GameState.h"

#include <set>

class StateMachineExampleGame;

class HighScoreState : public GameState
{
	StateMachineExampleGame* m_pOwner;
	std::set<int> m_HighScores;

public:
	HighScoreState(StateMachineExampleGame* pOwner);
	~HighScoreState() = default;

	virtual GameStateType GetType() override { return GameStateType::HighScore; }
	virtual void Draw() override;
	virtual void Update() override;
};

