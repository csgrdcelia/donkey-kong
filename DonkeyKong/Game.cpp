#include "pch.h"
#include "StringHelpers.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Game.h"
#include "Player.h"
#include "Ladder.h"
#include "Block.h"


const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: mWindow(sf::VideoMode(840, 600), "Donkey Kong 1981", sf::Style::Close)
	, mTexture()
	, mPlayer()
	, mFont()
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
	, mIsMovingUp(false)
	, mIsMovingDown(false)
	, mIsMovingRight(false)
	, mIsMovingLeft(false)
{
	mWindow.setFramerateLimit(160);

	EntityManager::DrawEntities();

	// Draw Peach
	mPeachTexture.loadFromFile("Media/Textures/peach.png");
	mPeach.setTexture(mPeachTexture);
	mPeach.setPosition(600.f, 55.f);

	// Draw Statistic Font 

	mFont.loadFromFile("Media/Sansation.ttf");
	mStatisticsText.setString("Welcome to Donkey Kong 1981");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);

	// Draw end game text
	mEndGameText.setFont(mFont);
	mEndGameText.setPosition(280.f, 10.f);
	mEndGameText.setCharacterSize(50);
	mEndGameText.setStyle(sf::Text::Bold);
	mEndGameText.setFillColor(sf::Color::Red);
	
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

	if (key == sf::Keyboard::Space)
	{
	}
}

void Game::update(sf::Time elapsedTime)
{
	if (mIsMovingUp)
		EntityManager::m_Player->GoUp(elapsedTime);
	if (mIsMovingDown)
		EntityManager::m_Player->GoDown(elapsedTime);
	if (mIsMovingLeft)
		EntityManager::m_Player->GoLeft(elapsedTime);
	if (mIsMovingRight)
		EntityManager::m_Player->GoRight(elapsedTime);

	EntityManager::m_Player->TryToEatCoin();

	for (std::shared_ptr<Enemy> enemy : EntityManager::m_Enemies)
	{
		enemy->Move(elapsedTime);
	}
}

void Game::render()
{
	mWindow.clear();

	for (std::shared_ptr<Entity> entity : EntityManager::m_Blocks)
	{
		if (entity->m_enabled)
			mWindow.draw(entity->m_sprite);
	}

	for (std::shared_ptr<Entity> entity : EntityManager::m_Ladders)
	{
		if (entity->m_enabled)
			mWindow.draw(entity->m_sprite);
	}

	for (std::shared_ptr<Entity> entity : EntityManager::m_Coins)
	{
		if (entity->m_enabled)
			mWindow.draw(entity->m_sprite);
	}

	for (std::shared_ptr<Entity> entity : EntityManager::m_Enemies)
	{
		if (entity->m_enabled)
			mWindow.draw(entity->m_sprite);
	}

	mWindow.draw(EntityManager::m_Player->m_sprite);
	mWindow.draw(Game::mPeach);

	
	mWindow.draw(mStatisticsText);
	mWindow.draw(mEndGameText);

	mWindow.display();
}

void Game::watchMario()
{
	std::shared_ptr<Player> mario = EntityManager::m_Player;
	if (mario->HasEatenAllCoins())
		this->IsWon();
	if (mario->HasCollidedEnemy())
		this->IsOver();
	if (mario->OnVoid())
		mario->GoDown(sf::microseconds(10000));
	if (mario->IsOutsideOfWindow())
		IsOver();
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
			toString(EntityManager::GetCoinsEaten()) + "/" + toString(EntityManager::m_Coins.size()) + " coins"
		);

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}


	if (mStatisticsUpdateTime >= sf::seconds(0.050f))
	{
		
	}
}

void Game::IsWon()
{
	IsFinished = true; 
	mEndGameText.setString("YOU WON !");
	
}

void Game::IsOver()
{
	IsFinished = true;
	mEndGameText.setString("GAME OVER !");
}



