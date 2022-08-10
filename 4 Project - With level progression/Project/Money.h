#pragma once
#include "PlacableActor.h"
#include "Player.h"

class Money : public PlacableActor
{
public:
	Money(int x, int y, int worth);

	int GetWorth() const { return m_worth; }

	virtual void HandleCollision(Player& player) override;
	virtual ActorType GetType() override { return ActorType::Money; }
	virtual void Draw() override;
private:
	int m_worth;
};

