#pragma once
#include "PlacableActor.h"
#include "Player.h"

class Door : public PlacableActor
{
public:
	Door(int x, int y, ActorColor color, ActorColor closedColor);
	virtual void Draw() override;

	virtual ActorType GetType() override { return ActorType::Door;  }
	virtual void HandleCollision(Player& player) override;

private:
	bool m_isOpen;
	ActorColor m_closedColor;
	void Open() { m_isOpen = true; }
};

