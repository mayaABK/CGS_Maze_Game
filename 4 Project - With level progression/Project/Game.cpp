#include "Game.h"

Game::Game()
	: m_pStateMachine(nullptr)
{

}

void Game::Initialize(GameStateMachine* pStateMachine)
{
	if (pStateMachine != nullptr)
	{
		pStateMachine->Init();
		m_pStateMachine = pStateMachine;
	}
}

void Game::RunGameLoop()
{
	while (!m_doQuitGame)
	{
		// check if level was beat
		CheckBeatLevel();

		// Draw
		Draw();


		Update();

		// The only way to quit the game play loop is when hits 4 to quit in MainMenuState
		m_doQuitGame = m_pStateMachine->DoQuitGame();
	}

	Draw();
}

void Game::Deinitialize()
{
	if (m_pStateMachine != nullptr)
		m_pStateMachine->Cleanup();
}

void Game::Update()
{
	m_pStateMachine->UpdateCurrentState();
}

void Game::CheckBeatLevel()
{
	m_pStateMachine->CheckBeatLevel();
}

void Game::Draw()
{
	m_pStateMachine->DrawCurrentState();
}
