#include "pch.h"
#include "Enemy.h"
#include "EntityManager.h"



Enemy::Enemy()
{
	Speed = 150.f;
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
			frameTimer = 100; // wait 100 frames before going up or down again
			IsGoingUp = false;
		}
	}
	else if (IsGoingDown)
	{
		if (!GoDown(elapsedTime))
		{
			frameTimer = 100; // wait 100 frames before going up or down again
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
	if (OnEdge())
	{
		if (Enemy::GoesToTheRight)
			Enemy::GoesToTheRight = false;
		else
			Enemy::GoesToTheRight = true;
	}
}