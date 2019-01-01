#include "pch.h"
#include "LevelFactory.h"

int LevelFactory::mCurrentLevel;
std::map<int, std::shared_ptr<Level>> LevelFactory::mLevels;

LevelFactory::LevelFactory()
{
	mCurrentLevel = 1;
	PopulateLevelMap();
}


LevelFactory::~LevelFactory()
{
}

std::shared_ptr<Level> LevelFactory::GetLevel()
{
	return mLevels.at(mCurrentLevel);
}

void LevelFactory::LevelUp()
{
	mCurrentLevel++;
}

void LevelFactory::Retry()
{
	PopulateLevelMap();
}

void LevelFactory::PopulateLevelMap()
{
	mLevels.clear();
	// LEVEL 1
	std::shared_ptr<Level> level1 = std::make_shared<Level>();
	mLevels.insert(std::pair<int, std::shared_ptr<Level>>(1, level1));

	level1->mPlayer = std::make_shared<Player>(170.f, 470.f);
	level1->mPeach = std::make_shared<Entity>(600.f, 55.f, "Media/Textures/peach.png");

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			std::shared_ptr<Block> se = std::make_shared<Block>(100.f + 70.f * (i + 1.f), 110.f * (j + 1.f));
			level1->mBlocks.push_back(se);
		}
	}

	// Ladders
	for (int i = 0; i < 4; i++)
	{
		std::shared_ptr<Ladder> se = std::make_shared<Ladder>(100.f + 70.f * (i + 3), 110.f * (i + 1) + 33);
		level1->mLadders.push_back(se);
	}

	// Coins
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::shared_ptr<Coin> se = std::make_shared<Coin>(100.f + 130.f * (j + 1), 110.f * (i + 1) + 50.f);
			if (!se->CollidesLadder(level1->mLadders))
				level1->mCoins.push_back(se);
		}
	}

	// Enemies
	for (int i = 0; i < 4; i++)
	{
		std::shared_ptr<Enemy> se = std::make_shared<Enemy>(100.f + 90.f * (i + 1), 110.f * (i + 1) + 78.f);
		level1->mEnemies.push_back(se);
	}

	// LEVEL 2
	std::shared_ptr<Level> level2 = std::make_shared<Level>();
	mLevels.insert(std::pair<int, std::shared_ptr<Level>>(2, level2));

	level2->mPlayer = std::make_shared<Player>(170.f, 470);
	level2->mPeach = std::make_shared<Entity>(600.f, 55.f, "Media/Textures/peach.png");

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			std::shared_ptr<Block> se = std::make_shared<Block>(100.f + 70.f * (i + 1.f), 110.f * (j + 1.f));
			level2->mBlocks.push_back(se);
		}
	}

	// Ladders
	for (int i = 0; i < 4; i++)
	{
		std::shared_ptr<Ladder> se = std::make_shared<Ladder>(100.f + 80.f * (i + 3), 110.f * (i + 1) + 33);
		level2->mLadders.push_back(se);
	}

	// Coins
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::shared_ptr<Coin> se = std::make_shared<Coin>(100.f + 130.f * (j + 1), 110.f * (i + 1) + 50.f);
			if (!se->CollidesLadder(level2->mLadders))
				level2->mCoins.push_back(se);
		}
	}

	// Enemies
	for (int i = 0; i < 4; i++)
	{
		std::shared_ptr<Enemy> se = std::make_shared<Enemy>(100.f + 90.f * (i + 1), 110.f * (i + 1) + 78.f);
		level2->mEnemies.push_back(se);
	}
}	
