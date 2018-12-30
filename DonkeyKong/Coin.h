#pragma once
#include "Entity.h"

class Coin : public Entity
{
public:
	Coin();
	Coin(float x, float y);
	~Coin();

public:
	bool CollidesLadder();
};

