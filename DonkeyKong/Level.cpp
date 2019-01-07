#include "pch.h"
#include "Level.h"


Level::Level()
{
}


Level::~Level()
{
}

int Level::GetCoinsEaten()
{
	int coins = 0;
	for (std::shared_ptr<Entity> entity : mCoins)
	{
		if (!entity->mEnabled)
		{
			coins += 1;
		}
	}
	return coins;
}

