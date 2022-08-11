#pragma once
#include "PlacableActor.h"

class Key;
class Weapon;

class Player : public PlacableActor
{
public:
	Player();

	bool HasKey();
	bool HasKey(ActorColor color);
	void PickupKey(Key* key);
	void UseKey();
	void DropKey();
	Key* GetKey() { return m_pCurrentKey; }

	bool isAlive() { return m_isAlive; }

	void AddMoney(int money) { m_money += money; }
	int GetMoney() { return m_money; }

	bool HasWeapon() { return m_hasWeapon; }
	void PickupWeapon(Weapon* weapon);
	void Shoot();

	void CollidedWithEnemy();

	int GetLives() { return m_lives; }

	virtual ActorType GetType() override { return ActorType::Player; }
	virtual void Draw() override;
	virtual void HandleCollision(Player& player) override {}

	void Wins() { m_wonGame = true; }
	void resetWin() { m_wonGame = false; }
	bool WonGame() { return m_wonGame; }
private:
	Key* m_pCurrentKey;
	int m_money;
	bool m_hasWeapon;
	Weapon* m_weapon;
	int m_lives;
	bool m_isAlive = true;
	bool m_wonGame = false;
};
