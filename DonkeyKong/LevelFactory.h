#pragma once
#include "Level.h"
class LevelFactory
{
public:
	LevelFactory();
	virtual ~LevelFactory();

public:
	static std::shared_ptr<Level> GetLevel();
	static void LevelUp();
	static void Retry();

private:
	static void PopulateLevelMap();

public:
	static int mCurrentLevel;
	static std::map<int, std::shared_ptr<Level>> mLevels;
};

