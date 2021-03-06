#pragma once

#define BLOCK_SPACE 110.f
#define COIN_SPACE 120.f
#define ENEMY_COUNT 4
#include "LevelFactory.h"
#include <SFML/Audio.hpp>

enum GameState
{
	Running,
	End
};

class Game
{
public:
	Game();
	virtual ~Game() { };
	void run();

private:
	void processEvents();
	void update(sf::Time elapsedTime);
	void render();
	void watchMario();

	void updateStatistics(sf::Time elapsedTime);
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void IsOver(int state);

	void IntroSound();

private:
	static const sf::Time	TimePerFrame;
	GameState		mGameState = GameState::Running;
	LevelFactory	mLevelFactory;

	sf::RenderWindow		mWindow;
	sf::Font	mFont;
	sf::Text	mStatisticsText;
	sf::Time	mStatisticsUpdateTime;
	sf::Text	mEndGameText;
	sf::Sprite	mPeach;
	sf::Texture mPeachTexture;

	std::size_t	mStatisticsNumFrames;

	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingRight;
	bool mIsMovingLeft;
	bool mEnterIsPressed;

	sf::SoundBuffer mIntroBuffer;
	sf::Sound mIntroSound;
	std::string mIntroSoundPath = "Media/Sounds/intro.wav";
};
