#pragma once
#include "Entity.h"
#include "Block.h"
#include "Ladder.h"
#include "Player.h"
#include "Coin.h"
#include "Enemy.h"

class Level
{
public:
	Level();
	virtual ~Level();

public:
	int GetCoinsEaten();

public:
	bool IsWon = false;
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<Entity> mPeach;
	std::vector<std::shared_ptr<Block>> mBlocks;
	std::vector<std::shared_ptr<Ladder>> mLadders;
	std::vector<std::shared_ptr<Coin>> mCoins;
	std::vector<std::shared_ptr<Enemy>> mEnemies;
};

