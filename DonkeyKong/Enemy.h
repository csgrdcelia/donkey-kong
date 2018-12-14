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

private:
	bool GoesToTheRight = true;
};

