#pragma once
#include "Entity.h"
class Enemy : public Entity
{
public:
	Enemy();
	~Enemy();

public:
	bool GoesToTheRight = true;

public:
	void ChangeSideIfOnEdge();
};

