#include "WinState.h"

#include <iostream>
#include <conio.h>

#include "StateMachineExampleGame.h"

using namespace std;


WinState::WinState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{
}

void WinState::Update()
{
	int input = _getch();
	m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
}

void WinState::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "          - - - WELL DONE - - -" << endl << endl;
	cout << "             You beat the game!" << endl << endl << endl;
	cout << "             Press any key to go back to the main menu" << endl << endl << endl;
}