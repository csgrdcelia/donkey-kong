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


bool Player::GoDown(sf::Time elapsedTime)
{
	if (this->IsAboveOrOnLadder() || OnVoid())
	{
		sf::Vector2f movement(0.f, 0.f);
		movement.y += Speed;
		this->m_sprite.move(movement * elapsedTime.asSeconds());
		return true;
	}
	return false;

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

// not working because it should render between moves...
void Player::Die(sf::Time elapsedTime)
{
	for (int i = 0; i < 30; i++)
	{
		this->GoUp(elapsedTime);
	}
	while (this->m_position.y > 0)
	{
		this->GoDown(sf::microseconds(15000));
	}
}


