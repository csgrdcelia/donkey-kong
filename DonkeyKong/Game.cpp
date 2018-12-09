#include "pch.h"
#include "StringHelpers.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Game.h"
#include "Player.h"
#include "Ladder.h"
#include "Block.h"


const float Game::PlayerSpeed = 100.f;
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

	// Draw blocks

	_TextureBlock.loadFromFile("Media/Textures/Block.png");
	_sizeBlock = _TextureBlock.getSize();

	for (int i = 0; i < BLOCK_COUNT_X; i++)
	{
		for (int j = 0; j < BLOCK_COUNT_Y; j++)
		{
			_Block[i][j].setTexture(_TextureBlock);
			_Block[i][j].setPosition(100.f + 70.f * (i + 1), BLOCK_SPACE * (j + 1));

			std::shared_ptr<Block> se = std::make_shared<Block>();
			se->m_sprite = _Block[i][j];
			se->m_size = _TextureBlock.getSize();
			se->m_position = _Block[i][j].getPosition();
			EntityManager::m_Blocks.push_back(se);
		}
	}

	// Draw Echelles

	_TextureEchelle.loadFromFile("Media/Textures/Echelle.png");

	for (int i = 0; i < ECHELLE_COUNT; i++)
	{
		_Echelle[i].setTexture(_TextureEchelle);
		_Echelle[i].setPosition(100.f + 70.f * (i + 1), BLOCK_SPACE * (i + 1) + _sizeBlock.y);

		std::shared_ptr<Ladder> se = std::make_shared<Ladder>();
		se->m_sprite = _Echelle[i];
		se->m_size = _TextureEchelle.getSize();
		se->m_position = _Echelle[i].getPosition();
		EntityManager::m_Ladders.push_back(se);
	}

	// Draw coins

	_textureCoin.loadFromFile("Media/Textures/coin.png");
	for (int i = 0; i < COIN_COUNT; i++)
	{
		for (int j = 0; j < COIN_COUNT; j++)
		{
			_coin[i][j].setTexture(_textureCoin);
			_coin[i][j].setPosition(100.f + 130.f * (j + 1), BLOCK_SPACE * (i + 1) + 50.f);

			std::shared_ptr<Coin> se = std::make_shared<Coin>();
			se->m_sprite = _coin[i][j];
			se->m_size = _textureCoin.getSize();
			se->m_position = _coin[i][j].getPosition();
			if(!se->CollidesLadder())
				EntityManager::m_Coins.push_back(se);
		}
	}

	// Draw Mario

	mTexture.loadFromFile("Media/Textures/Mario_small_transparent.png"); // Mario_small.png");
	_sizeMario = mTexture.getSize();
	mPlayer.setTexture(mTexture);
	sf::Vector2f posMario;
	posMario.x = 100.f + 70.f;
	posMario.y = BLOCK_SPACE * 5 - _sizeMario.y;

	mPlayer.setPosition(posMario);

	std::shared_ptr<Player> player = std::make_shared<Player>();
	player->m_sprite = mPlayer;
	player->m_size = mTexture.getSize();
	player->m_position = mPlayer.getPosition();
	EntityManager::m_Player = player;

	// Draw Statistic Font 

	mFont.loadFromFile("Media/Sansation.ttf");
	mStatisticsText.setString("Welcome to Donkey Kong 1981");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
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
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp && EntityManager::m_Player->IsUnderLadder())
		movement.y -= PlayerSpeed;
	if (mIsMovingDown && EntityManager::m_Player->IsAboveLadder())
		movement.y += PlayerSpeed;
	if (mIsMovingLeft)
		movement.x -= PlayerSpeed;
	if (mIsMovingRight)
		movement.x += PlayerSpeed;

	EntityManager::m_Player->m_sprite.move(movement * elapsedTime.asSeconds());

	EntityManager::m_Player->TryToEatCoin();

}

void Game::render()
{
	mWindow.clear();

	for (std::shared_ptr<Entity> entity : EntityManager::m_Blocks)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}
		mWindow.draw(entity->m_sprite);
	}

	for (std::shared_ptr<Entity> entity : EntityManager::m_Ladders)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}
		mWindow.draw(entity->m_sprite);
	}

	for (std::shared_ptr<Entity> entity : EntityManager::m_Coins)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}
		mWindow.draw(entity->m_sprite);
	}

	mWindow.draw(EntityManager::m_Player->m_sprite);

	mWindow.draw(mStatisticsText);
	mWindow.display();
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


