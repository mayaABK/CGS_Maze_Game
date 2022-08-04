#include <iostream>
#include <windows.h>

#include "Weapon.h"

void Weapon::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)m_color);

	std::cout << char(WeaponDirection::Right);
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}

void Weapon::DrawBullet()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)m_color);

	std::cout << char(46);
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}