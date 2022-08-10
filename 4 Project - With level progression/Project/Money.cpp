#include <iostream>
#include "Money.h"
#include "AudioManager.h"
#include "Player.h"

Money::Money(int x, int y, int worth)
	: PlacableActor(x, y)
	, m_worth(worth)
{

}

void Money::Draw()
{
	std::cout << "$";
}

void Money::HandleCollision(Player& player)
{
	AudioManager::GetInstance()->PlayMoneySound();
	Remove();
	player.AddMoney(GetWorth());
	player.SetPosition(m_pPosition->x, m_pPosition->y);
}
