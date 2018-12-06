#pragma once
#include "pch.h"
#include "Entity.h"

class Player : public Entity
{
public:
	Player();
	~Player();

public:
	bool IsUnderLadder();
	bool IsAboveLadder();
private:
	bool CollidesBlock();

public:
	static const float	PlayerSpeed;
	

};

