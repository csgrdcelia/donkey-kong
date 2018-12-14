#pragma once
#include "pch.h"
#include "Entity.h"

class Player : public Entity
{
public:
	Player();
	~Player();

public:
	void Die(sf::Time elapsedTime);
	void TryToEatCoin();
	bool HasEatenAllCoins();
	bool HasCollidedEnemy();
	


	

};

