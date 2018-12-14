#include "pch.h"
#include "Entity.h"
#include "EntityManager.h"

void Entity::GoRight(sf::Time elapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);
	movement.x += Speed;
	this->m_sprite.move(movement * elapsedTime.asSeconds());
}

void Entity::GoLeft(sf::Time elapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);
	movement.x -= Speed;
	this->m_sprite.move(movement * elapsedTime.asSeconds());
}

void Entity::GoUp(sf::Time elapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);
	if (this->IsUnderLadder())
	{
		movement.y -= Speed;
	}
	this->m_sprite.move(movement * elapsedTime.asSeconds());
}

void Entity::GoDown(sf::Time elapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);
	if (this->IsAboveLadder())
	{
		movement.y += Speed;
	}
	this->m_sprite.move(movement * elapsedTime.asSeconds());
}

bool Entity::IsUnderLadder()
{
	for (std::shared_ptr<Entity> entity : EntityManager::m_Ladders)
	{
		sf::FloatRect fr = entity->m_sprite.getGlobalBounds();
		fr.top -= 32; // so it can continue to hike when it's on the block
		if (this->m_sprite.getGlobalBounds().intersects(fr))
		{
			return true;
			break;
		}
	}
	return false;
}

bool Entity::IsAboveLadder()
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

bool Entity::CollidesBlock() {
	for (std::shared_ptr<Entity> entity : EntityManager::m_Blocks)
	{
		if (this->m_sprite.getGlobalBounds().intersects(entity->m_sprite.getGlobalBounds()))
		{
			return true;
		}
	}
	return false;
}
