#include <iostream>
#include <windows.h>

#include "Key.h"
#include "AudioManager.h"
#include "Player.h"

void Key::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)m_color);

	std::cout << "+";
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}

void Key::HandleCollision(Player& player)
{
	if (!player.HasKey())
	{
		player.PickupKey(this);
		Remove();
		player.SetPosition(m_pPosition->x, m_pPosition->y);
		AudioManager::GetInstance()->PlayKeyPickupSound();
	}
}
