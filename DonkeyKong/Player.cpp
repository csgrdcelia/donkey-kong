#include "pch.h"
#include "Player.h"
#include "EntityManager.h"

const float Player::PlayerSpeed = 100.f;

Player::Player()
{
}


Player::~Player()
{
}

bool Player::IsUnderLadder()
{
	for (std::shared_ptr<Entity> entity : EntityManager::m_Ladders)
	{
		sf::FloatRect fr = entity->m_sprite.getGlobalBounds();
		fr.top -= 30; // so Mario can continue to hike when he's on the block
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
		fr.top -= 32;
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

