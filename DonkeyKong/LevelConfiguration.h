#pragma once
#include "Player.h"
#include "Block.h"
class LevelConfiguration
{
public:
	LevelConfiguration(int level);
	virtual ~LevelConfiguration();

public:
	std::shared_ptr<Player> GetPlayer();
	std::vector<std::shared_ptr<Block>> GetBlocks();

private:
	int mLevel;
};

