#pragma once
#include "Entity.h"
#include "Ladder.h"

class Coin : public Entity
{
public:
	Coin();
	Coin(float x, float y);
	~Coin();

public:
	bool CollidesLadder(std::vector<std::shared_ptr<Ladder>> mLadders);
};

