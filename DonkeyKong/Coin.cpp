#include "pch.h"
#include "Coin.h"
#include "EntityManager.h"


Coin::Coin()
{
}


Coin::~Coin()
{
}

bool Coin::CollidesLadder()
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