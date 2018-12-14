#pragma once
#include "pch.h"
#include "Entity.h"

class Player : public Entity
{
public:
	Player();
	~Player();

public:
	void GoRight(sf::Time elapsedTime);
	void GoLeft(sf::Time elapsedTime);
	void GoUp(sf::Time elapsedTime);
	void GoDown(sf::Time elapsedTime);
	void Die(sf::Time elapsedTime);
	void TryToEatCoin();
	bool HasEatenAllCoins();
	bool HasCollidedEnemy();
	
private:
	bool CollidesBlock();
	bool IsUnderLadder();
	bool IsAboveLadder();

private:
	const float	PlayerSpeed;
	

};

