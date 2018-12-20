#pragma once
#include "pch.h"
#include "Entity.h"

class Player : public Entity
{
public:
	Player();
	~Player();
	

public:
	void TryToEatCoin();
	bool HasEatenAllCoins();
	bool HasCollidedEnemy();
	bool GoDown(sf::Time elapsedTime);
	
	void Jump(sf::Time elapsedTime);
};

