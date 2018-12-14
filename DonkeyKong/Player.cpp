#include "pch.h"
#include "Player.h"
#include "EntityManager.h"


Player::Player() : PlayerSpeed(150.f)
{
}


Player::~Player()
{
}

void Player::GoRight(sf::Time elapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);
	movement.x += PlayerSpeed;
	this->m_sprite.move(movement * elapsedTime.asSeconds());
}

void Player::GoLeft(sf::Time elapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);
	movement.x -= PlayerSpeed;
	this->m_sprite.move(movement * elapsedTime.asSeconds());
}

void Player::GoUp(sf::Time elapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);
	if (this->IsUnderLadder())
	{
		movement.y -= PlayerSpeed;
	}
	this->m_sprite.move(movement * elapsedTime.asSeconds());
}

void Player::GoDown(sf::Time elapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);
	if (this->IsAboveLadder())
	{
		movement.y += PlayerSpeed;
	}
	this->m_sprite.move(movement * elapsedTime.asSeconds());
}

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

bool Player::IsUnderLadder()
{
	for (std::shared_ptr<Entity> entity : EntityManager::m_Ladders)
	{
		sf::FloatRect fr = entity->m_sprite.getGlobalBounds();
		fr.top -= 32; // so Mario can continue to hike when he's on the block
		if (this->m_sprite.getGlobalBounds().intersects(fr))
		{
			return true;
			break;
		}
	}
	return false;
}

bool Player::IsAboveLadder()
{
	for (std::shared_ptr<Entity> entity : EntityManager::m_Ladders)
	{
		sf::FloatRect fr = entity->m_sprite.getGlobalBounds();
		fr.top -= 40;
		if (EntityManager::m_Player->m_sprite.getGlobalBounds().intersects(fr))
		{
			return true;
			break;
		}
	}
	return false;
}

bool Player::CollidesBlock() {
	for (std::shared_ptr<Entity> entity : EntityManager::m_Blocks)
	{
		if (EntityManager::m_Player->m_sprite.getGlobalBounds().intersects(entity->m_sprite.getGlobalBounds()))
		{
			return true;
		}
	}
	return false;
}

