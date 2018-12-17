#include "pch.h"
#include "Player.h"
#include "EntityManager.h"


Player::Player() 
{
	Speed = 150.f;
}


Player::~Player()
{
}



void Player::TryToEatCoin()
{
	for (std::shared_ptr<Entity> entity : EntityManager::m_Coins)
	{
		sf::FloatRect fr = entity->m_sprite.getGlobalBounds();
		if (this->m_sprite.getGlobalBounds().intersects(fr))
		{
			entity->m_enabled = false;
			break;
		}
	}
}

bool Player::HasEatenAllCoins()
{
	if (EntityManager::GetCoinsEaten() == EntityManager::m_Coins.size())
	{
		return true;
	}
	return false;
}

bool Player::HasCollidedEnemy()
{
	for (std::shared_ptr<Entity> entity : EntityManager::m_Enemies)
	{
		sf::FloatRect fr = entity->m_sprite.getGlobalBounds();
		if (this->m_sprite.getGlobalBounds().intersects(fr))
		{
			return true;
		}
	}
	return false;
}


