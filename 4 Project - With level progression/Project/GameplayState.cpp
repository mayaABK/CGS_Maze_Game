#include "GameplayState.h"

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>

#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Money.h"
#include "Weapon.h"
#include "Goal.h"
#include "AudioManager.h"
#include "Utility.h"
#include "StateMachineExampleGame.h"

using namespace std;

constexpr int kArrowInput = 224;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;
constexpr int kEscapeKey = 27;

GameplayState::GameplayState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
	, m_skipFrameCount(0)
	, m_currentLevel(0)
	, m_pLevel(nullptr)
{
	m_LevelNames.push_back("Level1.txt");
	m_LevelNames.push_back("Level2.txt");
	m_LevelNames.push_back("Level3.txt");
}

GameplayState::~GameplayState()
{
	delete m_pLevel;
	m_pLevel = nullptr;
}

bool GameplayState::Load()
{
	if (m_pLevel)
	{
		delete m_pLevel;
		m_pLevel = nullptr;
	}

	m_pLevel = new Level();
	
	return m_pLevel->Load(m_LevelNames.at(m_currentLevel), m_player.GetXPositionPointer(), m_player.GetYPositionPointer());

}

void GameplayState::Enter()
{
	Load();
}

bool GameplayState::BulletIsTraveling(int x, int y)
{
	if (m_pLevel->BulletHitActor(x, y))
	{
		return false;
	}
	else if (m_pLevel->IsSpace(x, y))
	{
		DrawTravelingBullet(x, y);
		return true;
	}
	else {
		//hit a wall
		return false;
	}
}

void GameplayState::UpdateShooting(char input)
{
	int x;
	int y;
	bool bulletIsTraveling = true;
	if (input == 'i' || input == 'I')
	{
		x = m_player.GetXPosition();
		y = m_player.GetYPosition() - 1;
		for (y; y > 0 && bulletIsTraveling; y--)
		{
			bulletIsTraveling = BulletIsTraveling(x, y);
		}

	}
	else if (input == 'j' || input == 'J')
	{
		x = m_player.GetXPosition() - 1;
		y = m_player.GetYPosition();

		for (x; x > 0 && bulletIsTraveling; x--)
		{
			bulletIsTraveling = BulletIsTraveling(x, y);
		}

	}
	else if (input == 'k' || input == 'K') 
		// This breakpoint was placed when I was debugging why the bullet would travel through enemies inside the level
		// By using the debugger, I realized that I had assumed that m_pLevelData would include all playable actors on it.
		// However, playable actors are simply printed on screen after the m_pLevelData prints the level outline
	{
		x = m_player.GetXPosition();
		y = m_player.GetYPosition() + 1;
		for (y; y < m_pLevel->GetHeight() - 1 && bulletIsTraveling; y++)
		{
			bulletIsTraveling = BulletIsTraveling(x, y);
		}
	}
	else if (input == 'l' || input == 'L')
	{
		x = m_player.GetXPosition() + 1;
		y = m_player.GetYPosition();

		for (x; x < m_pLevel->GetWidth() - 1 && bulletIsTraveling; x++)
		{
			bulletIsTraveling = BulletIsTraveling(x, y);
		}
	}
	
}

void GameplayState::ProcessInput()
{
	int input = _getch();
	int arrowInput = 0;
	int newPlayerX = m_player.GetXPosition();
	int newPlayerY = m_player.GetYPosition();

	// One of the arrow keys were pressed
	if (input == kArrowInput)
	{
		arrowInput = _getch();
	}

	if ((input == kArrowInput && arrowInput == kLeftArrow) ||
		(char)input == 'A' || (char)input == 'a')
	{
		newPlayerX--;
	}
	else if ((input == kArrowInput && arrowInput == kRightArrow) ||
		(char)input == 'D' || (char)input == 'd')
	{
		newPlayerX++;
	}
	else if ((input == kArrowInput && arrowInput == kUpArrow) ||
		(char)input == 'W' || (char)input == 'w')
	{
		newPlayerY--;
	}
	else if ((input == kArrowInput && arrowInput == kDownArrow) ||
		(char)input == 'S' || (char)input == 's')
	{
		newPlayerY++;
	}
	else if ((char)input == 'I' || (char)input == 'i' || (char)input == 'J' || (char)input == 'j' || (char)input == 'K' || (char)input == 'k' || (char)input == 'L' || (char)input == 'l')
	{
		if (m_player.HasWeapon())
		{
			UpdateShooting((char)input);
		}
	}
	else if (input == kEscapeKey)
	{
		m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
	}
	else if ((char)input == 'Z' || (char)input == 'z')
	{
		m_player.DropKey();
	}

	// If position never changed
	if (newPlayerX == m_player.GetXPosition() && newPlayerY == m_player.GetYPosition())
	{
		//return false;
	}
	else
	{
		HandleCollision(newPlayerX, newPlayerY);
	}
}

void GameplayState::CheckBeatLevel()
{
	if (m_pLevel->DidBeatLevel())
	{
		++m_skipFrameCount;
		if (m_skipFrameCount > kFramesToSkip)
		{
			m_player.resetWin();
			m_skipFrameCount = 0;
			++m_currentLevel;
			if (m_currentLevel == m_LevelNames.size())
			{
				Utility::WriteHighScore(m_player.GetMoney());

				AudioManager::GetInstance()->PlayWinSound();

				m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Win);
			}
			else
			{
				// On to the next level
				Load();
			}
		}
	}
}


void GameplayState::Update()
{
	if (!m_pLevel->DidBeatLevel())
	{
		ProcessInput();
	}

	CheckBeatLevel();
}

void GameplayState::HandleCollision(int newPlayerX, int newPlayerY)
{
	PlacableActor* collidedActor = m_pLevel->UpdateActors(m_player.GetXPosition(), m_player.GetYPosition(), newPlayerX, newPlayerY);
	if (collidedActor != nullptr)
	{
		collidedActor->HandleCollision(m_player);

		if (m_player.WonGame())
		{
			m_pLevel->FinishedLevel();
		}
		else if (!(m_player.isAlive()))
		{
			//TODO: Go to game over screen
			AudioManager::GetInstance()->PlayLoseSound();
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Lose);
		}
	}
	else if (m_pLevel->IsSpace(newPlayerX, newPlayerY)) // no collision
	{
		m_player.SetPosition(newPlayerX, newPlayerY);
	}
	else if (m_pLevel->IsWall(newPlayerX, newPlayerY))
	{
		// wall collision, do nothing
	}
}

void GameplayState::DrawTravelingBullet(int x, int y)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	m_pLevel->Draw();

	// Set cursor position for player 
	COORD actorCursorPosition;
	actorCursorPosition.X = m_player.GetXPosition();
	actorCursorPosition.Y = m_player.GetYPosition();
	SetConsoleCursorPosition(console, actorCursorPosition);
	m_player.Draw();

	// Set cursor for bullet
	COORD bulletPosition;
	bulletPosition.X = x;
	bulletPosition.Y = y;
	SetConsoleCursorPosition(console, bulletPosition);
	m_player.Shoot();

	// Set the cursor to the end of the level
	COORD currentCursorPosition;
	currentCursorPosition.X = 0;
	currentCursorPosition.Y = m_pLevel->GetHeight();
	SetConsoleCursorPosition(console, currentCursorPosition);

	DrawHUD(console);
	

	Sleep(100);
}


void GameplayState::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	m_pLevel->Draw();

	// Set cursor position for player 
	COORD actorCursorPosition;
	actorCursorPosition.X = m_player.GetXPosition();
	actorCursorPosition.Y = m_player.GetYPosition();
	SetConsoleCursorPosition(console, actorCursorPosition);
	m_player.Draw();

	// Set the cursor to the end of the level
	COORD currentCursorPosition;
	currentCursorPosition.X = 0;
	currentCursorPosition.Y = m_pLevel->GetHeight();
	SetConsoleCursorPosition(console, currentCursorPosition);

	DrawHUD(console);
}

void GameplayState::DrawHUD(const HANDLE& console)
{
	cout << endl;

	// Top Border
	for (int i = 0; i < m_pLevel->GetWidth(); ++i)
	{
		cout << Level::WAL;
	}
	cout << endl;

	int consoleWidth = (int)m_pLevel->GetWidth() - 2;

	//Additional instructions
	cout << Level::WAL;
	cout << setw(consoleWidth) << left << " ijkl-shoot " << Level::WAL << endl;

	// Left Side border
	cout << Level::WAL;


	cout << " wasd-move " << Level::WAL << " z-drop key " << Level::WAL;

	cout << " $:" << m_player.GetMoney() << " " << Level::WAL;
	cout << " lives:" << m_player.GetLives() << " " << Level::WAL;
	cout << " key:";
	if (m_player.HasKey())
	{
		m_player.GetKey()->Draw();
	}
	else
	{
		cout << " ";
	}

	// RightSide border 
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(console, &csbi);
	COORD pos;
	pos.X = m_pLevel->GetWidth() - 1;
	pos.Y = csbi.dwCursorPosition.Y;
	SetConsoleCursorPosition(console, pos);

	cout << Level::WAL;
	cout << endl;

	// Bottom Border
	for (int i = 0; i < m_pLevel->GetWidth(); ++i)
	{
		cout << Level::WAL;
	}
	cout << endl;
}