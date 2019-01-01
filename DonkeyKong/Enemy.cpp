#include "pch.h"
#include "Enemy.h"



Enemy::Enemy()
{
}

Enemy::Enemy(float x, float y) : Entity(x, y)
{
	m_speed = 100.f;

	m_texture.loadFromFile("Media/Textures/enemy_1_right.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(x, y);
}

Enemy::~Enemy()
{
}

void Enemy::Move(sf::Time elapsedTime)
{
	if (IsGoingUp)
	{
		if (!GoUp(elapsedTime))
		{
			frameTimer = rand() % (700 - 30) + 30; // wait between 30 and 700 frames before going up or down again
			IsGoingUp = false;
		}
	}
	else if (IsGoingDown)
	{
		if (!GoDown(elapsedTime))
		{
			frameTimer = rand() % (700 - 30) + 30; // wait between 30 and 700 frames before going up or down again
			IsGoingDown = false;
		}
	}
	else
	{
		if (frameTimer == 0)
		{
			if (GoDown(elapsedTime))
				IsGoingDown = true;
			else if (GoUp(elapsedTime))
				IsGoingUp = true;
			else
				GoLeftOrRight(elapsedTime);
		}
		else
		{
			frameTimer -= 1;
			GoLeftOrRight(elapsedTime);
		}
	}
}

void Enemy::GoLeftOrRight(sf::Time elapsedTime)
{
	ChangeSideIfOnEdge();
	if (GoesToTheRight)
		GoRight(elapsedTime);
	else
		GoLeft(elapsedTime);
}

void Enemy::ChangeSideIfOnEdge()
{
	if (OnVoid())
	{
		if (Enemy::GoesToTheRight)
			Enemy::GoesToTheRight = false;
		else
			Enemy::GoesToTheRight = true;
	}
}