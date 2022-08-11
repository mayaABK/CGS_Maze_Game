#include <iostream>
#include "Goal.h"
#include "Player.h"

Goal::Goal(int x, int y)
	: PlacableActor(x, y)
{
	
}

void Goal::Draw()
{
	std::cout << "X";
}

void Goal::HandleCollision(Player& player)
{
	this->Remove();
	player.SetPosition(m_pPosition->x, m_pPosition->y);
	player.Wins();
}