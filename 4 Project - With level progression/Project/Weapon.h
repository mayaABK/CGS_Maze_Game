#pragma once
#include "PlacableActor.h"

enum class WeaponDirection
{
	Right = 169
};

class Weapon : public PlacableActor
{
public:
	Weapon(int x, int y, ActorColor color)
		: PlacableActor(x, y, color)
	{

	}

	virtual ActorType GetType() override { return ActorType::Weapon; }
	virtual void Draw() override;
	void DrawBullet();

private:
	WeaponDirection m_direction;
};

