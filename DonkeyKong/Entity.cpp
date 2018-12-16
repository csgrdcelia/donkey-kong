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

bool Entity::GoUp(sf::Time elapsedTime)
{
	if (this->IsOnLadder())
	{
		sf::Vector2f movement(0.f, 0.f);
		movement.y -= Speed;
		this->m_sprite.move(movement * elapsedTime.asSeconds());
		return true;
	}
	return false;
}

bool Entity::GoDown(sf::Time elapsedTime)
{
	if (this->IsAboveOrOnLadder())
	{
		sf::Vector2f movement(0.f, 0.f);
		movement.y += Speed;
		this->m_sprite.move(movement * elapsedTime.asSeconds());
		return true;
	}
	return false;
	
}

bool Entity::IsOnLadder()
{
	for (std::shared_ptr<Entity> entity : EntityManager::m_Ladders)
	{
		sf::FloatRect fr = entity->m_sprite.getGlobalBounds();
		fr.top -= 33; // we add the height of the block texture so our entity can hike on it
		fr.height += 33; 
		if (this->m_sprite.getGlobalBounds().intersects(fr))
		{
			return true;
		}
	}
	return false;
}

bool Entity::IsAboveOrOnLadder()
{
	for (std::shared_ptr<Entity> entity : EntityManager::m_Ladders)
	{
		sf::FloatRect fr = entity->m_sprite.getGlobalBounds();
		fr.top -= this->m_size.y + 10;
		fr.height += 15;
		if (this->m_sprite.getGlobalBounds().intersects(fr))
		{
			return true;
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

bool Entity::OnEdge()
{
	bool OnEdge = true;
	for (std::shared_ptr<Entity> entity : EntityManager::m_Blocks)
	{
		sf::FloatRect fr = entity->m_sprite.getGlobalBounds();
		fr.top -= 5;
		if (this->m_sprite.getGlobalBounds().intersects(fr))
		{
			OnEdge = false;
		}
	}
	return OnEdge;
}
