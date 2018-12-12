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
	bool IsUnderLadder();
	bool IsAboveLadder();
private:
	bool CollidesBlock();

public:
	static const float	PlayerSpeed;
	

};

