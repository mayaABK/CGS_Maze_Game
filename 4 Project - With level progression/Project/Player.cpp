#include <iostream>

#include "Player.h"
#include "Key.h"
#include "Weapon.h"
#include "AudioManager.h"

using namespace std;

constexpr int kStartingNumberOfLives = 3;

Player::Player()
	: PlacableActor(0, 0)
	, m_pCurrentKey(nullptr)
	, m_money(0)
	, m_hasWeapon(false)
	, m_weapon(nullptr)
	, m_lives(kStartingNumberOfLives)
{

}

bool Player::HasKey()
{
	return m_pCurrentKey != nullptr;
}

bool Player::HasKey(ActorColor color)
{
	return HasKey() && m_pCurrentKey->GetColor() == color;
}

void Player::PickupKey(Key* key)
{
	m_pCurrentKey = key;
}

void Player::UseKey()
{
	if (m_pCurrentKey)
	{
		m_pCurrentKey->Remove();
		m_pCurrentKey = nullptr;
	}
}

void Player::DropKey()
{
	if (m_pCurrentKey)
	{
		AudioManager::GetInstance()->PlayKeyDropSound();
		m_pCurrentKey->Place(m_pPosition->x, m_pPosition->y);
		m_pCurrentKey = nullptr;
	}
}

void Player::PickupWeapon(Weapon* weapon)
{
	m_hasWeapon = true; 
	m_weapon = weapon;
}

void Player::Shoot()
{
	m_weapon->DrawBullet();
}

void Player::CollidedWithEnemy()
{
	m_lives--;

	if (m_lives == 0)
	{
		m_isAlive = false;
	}
}

void Player::Draw()
{
	cout << "@";
}