#include "pch.h"
#include "StringHelpers.h"
#include "Entity.h"
#include "Game.h"
#include "Player.h"
#include "Ladder.h"
#include "Block.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: mWindow(sf::VideoMode(840, 600), "Donkey Kong 1981", sf::Style::Close)
	, mFont()
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
	, mIsMovingUp(false)
	, mIsMovingDown(false)
	, mIsMovingRight(false)
	, mIsMovingLeft(false)
{
	mWindow.setFramerateLimit(60);

	// Draw Statistic Font
	mFont.loadFromFile("Media/Sansation.ttf");
	mStatisticsText.setString("Welcome to Donkey Kong 1981");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(20);

	// Draw end game text
	mEndGameText.setFont(mFont);
	mEndGameText.setPosition(280.f, 10.f);
	mEndGameText.setCharacterSize(45);
	mEndGameText.setStyle(sf::Text::Bold);
	mEndGameText.setFillColor(sf::Color::Red);

	IntroSound();
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}

		updateStatistics(elapsedTime);
		render();

		if (mGameState != GameState::End) 
			watchMario();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Up)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::Down)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::Left)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::Right)
		mIsMovingRight = isPressed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && mLevelFactory.GetLevel()->mPlayer->cptFall == 10) {
		mWindow.setKeyRepeatEnabled(false);
		if(mLevelFactory.GetLevel()->mPlayer->cptFall == 10)
			mLevelFactory.GetLevel()->mPlayer->mIsJumping = true;
	}
	else if (key == sf::Keyboard::Return)
		mEnterIsPressed = isPressed;
}

void Game::update(sf::Time elapsedTime)
{
	switch(mGameState)
	{

	case GameState::Running:
		if (mIsMovingUp)
			mLevelFactory.GetLevel()->mPlayer->GoUp(elapsedTime);
		
		if (mIsMovingDown)
			mLevelFactory.GetLevel()->mPlayer->GoDown(elapsedTime);

		if (mIsMovingLeft)
			mLevelFactory.GetLevel()->mPlayer->GoLeft(elapsedTime);

		if (mIsMovingRight)
			mLevelFactory.GetLevel()->mPlayer->GoRight(elapsedTime);

		if (mLevelFactory.GetLevel()->mPlayer->mIsJumping)
			mLevelFactory.GetLevel()->mPlayer->Jump(elapsedTime);

		mLevelFactory.GetLevel()->mPlayer->TryToEatCoin();

		for (std::shared_ptr<Enemy> enemy : mLevelFactory.GetLevel()->mEnemies)
			enemy->Move(elapsedTime);

		break;

	case GameState::End:
		for (std::shared_ptr<Enemy> enemy : mLevelFactory.GetLevel()->mEnemies)
			enemy->Move(elapsedTime);

		if (mEnterIsPressed)
		{
			if (mLevelFactory.GetLevel()->IsWon)
			{
				mLevelFactory.LevelUp();
				IntroSound();
			}
			else
			{
				mLevelFactory.Retry();
			}

			mEndGameText.setString("");
			mGameState = GameState::Running;
		}

		break;
	}
}

void Game::render()
{
	mWindow.clear();

	for (std::shared_ptr<Entity> entity : mLevelFactory.GetLevel()->mBlocks)
	{
		if (entity->mEnabled)
			mWindow.draw(entity->mSprite);
	}

	for (std::shared_ptr<Entity> entity : mLevelFactory.GetLevel()->mLadders)
	{
		if (entity->mEnabled)
			mWindow.draw(entity->mSprite);
	}

	for (std::shared_ptr<Entity> entity : mLevelFactory.GetLevel()->mCoins)
	{
		if (entity->mEnabled)
			mWindow.draw(entity->mSprite);
	}

	for (std::shared_ptr<Entity> entity : mLevelFactory.GetLevel()->mEnemies)
	{
		if (entity->mEnabled)
			mWindow.draw(entity->mSprite);
	}

	mWindow.draw(mLevelFactory.GetLevel()->mPlayer->mSprite);
	mWindow.draw(mLevelFactory.GetLevel()->mPeach->mSprite);

	mWindow.draw(mStatisticsText);
	mWindow.draw(mEndGameText);

	mWindow.display();
}

void Game::watchMario()
{
	std::shared_ptr<Player> mario = mLevelFactory.GetLevel()->mPlayer;
	
	if (mario->HasEatenAllCoins())
	{
		mario->WinSound();
		this->IsOver(1);
	}
	if (mario->HasCollidedEnemy()){
		mario->DieSound();
		this->IsOver(0);
	}
	if ((mario->OnVoid() && !mario->mIsJumping && mario->cptFly == 0) || (mario->IsOnLadder() && !mario->mIsJumping && mario->cptFall != 10))
		mario->GoDown(sf::microseconds(10000));
	if (mario->IsOutsideOfWindow())
		IsOver(0);
	mario->GravityHandle();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us\n" +
			toString(mLevelFactory.GetLevel()->GetCoinsEaten()) + "/" + toString(mLevelFactory.GetLevel()->mCoins.size()) + " coins"
		);

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}


	if (mStatisticsUpdateTime >= sf::seconds(0.050f))
	{

	}
}

void Game::IsOver(int state)
{
	mGameState = GameState::End;
	if (state == 0)
	{
		mEndGameText.setString("GAME OVER !\nRetry?");
	}
	else
	{
		mLevelFactory.GetLevel()->IsWon = true;
		mEndGameText.setString("YOU WON !\nEnter for next level");
	}
}

void Game::IntroSound()
{
	if (mIntroBuffer.loadFromFile(mIntroSoundPath))
	{
		mIntroSound.setBuffer(mIntroBuffer);
		mIntroSound.play();
		mIntroSound.setPlayingOffset(sf::seconds(2.f));
	}
}
