#pragma once
#include "GameState.h"
#include "Player.h"
#include "Level.h"

#include <windows.h>
#include <vector>
#include <string>

class StateMachineExampleGame;

class GameplayState : public GameState
{
	StateMachineExampleGame* m_pOwner;
	
	Player m_player;
	Level* m_pLevel;

	int m_skipFrameCount;
	static constexpr int kFramesToSkip = 2;

	int m_currentLevel;

	std::vector<std::string> m_LevelNames;

public:
	GameplayState(StateMachineExampleGame* pOwner);
	~GameplayState();

	virtual GameStateType GetType() override { return GameStateType::Gameplay; }

	virtual void Enter() override;
	virtual void Draw() override;
	void DrawTravelingBullet(int x, int y);
	virtual void Update() override;
	void CheckBeatLevel();

private:
	void HandleCollision(int newPlayerX, int newPlayerY);
	bool Load();
	void DrawHUD(const HANDLE& console);
	void UpdateShooting(char input);
	bool BulletIsTraveling(int x, int y);
	void ProcessInput();
};
