#include "pch.h"
#include "Enemy.h"
#include "EntityManager.h"



Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::ChangeSideIfOnEdge()
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
	if (OnEdge)
	{
		if (Enemy::GoesToTheRight)
			Enemy::GoesToTheRight = false;
		else
			Enemy::GoesToTheRight = true;
	}
}