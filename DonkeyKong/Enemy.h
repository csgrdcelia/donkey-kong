#pragma once
#include "Entity.h"
class Enemy : public Entity
{
public:
	Enemy();
	~Enemy();

public:
	void Move(sf::Time elapsedTime);

private:
	void ChangeSideIfOnEdge();
	void GoLeftOrRight(sf::Time elapsedTime);

private:
	bool GoesToTheRight = true;
	bool IsGoingUp = false;
	bool IsGoingDown = false;
	int frameTimer = 0;
};

