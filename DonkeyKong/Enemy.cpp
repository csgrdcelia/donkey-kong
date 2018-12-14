#include "pch.h"
#include "Enemy.h"
#include "EntityManager.h"



Enemy::Enemy() 
{
	Speed = 50.f;
}

Enemy::~Enemy()
{
}

void Enemy::Move(sf::Time elapsedTime)
{
	if (IsUnderLadder())
		GoUp(elapsedTime);
	else {
		this->ChangeSideIfOnEdge();
		sf::Vector2f movement(0.f, 0.f);
		if (this->GoesToTheRight)
			movement.x += Speed;
		else
			movement.x -= Speed;
		this->m_sprite.move(movement * elapsedTime.asSeconds());
	}
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