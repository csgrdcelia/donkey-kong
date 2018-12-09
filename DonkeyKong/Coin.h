#pragma once
#include "Entity.h"

class Coin : public Entity
{
public:
	Coin();
	~Coin();

public:
	bool CollidesLadder();
};

