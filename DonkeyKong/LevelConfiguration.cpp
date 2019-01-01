#include "pch.h"
#include "LevelConfiguration.h"


LevelConfiguration::LevelConfiguration(int level)
{
	mLevel = level;
}


LevelConfiguration::~LevelConfiguration()
{
}

std::shared_ptr<Player> LevelConfiguration::GetPlayer()
{
	switch (mLevel)
	{
	case 1 :
		return std::make_shared<Player>(170.f, 510.f);
		break;
	}
}

std::vector<std::shared_ptr<Block>> LevelConfiguration::GetBlocks()
{
	return std::vector<std::shared_ptr<Block>>();
}


