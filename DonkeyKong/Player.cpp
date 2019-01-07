#include "pch.h"
#include "Player.h"
#include "LevelFactory.h"


Player::Player(float x, float y) : Entity(x, y)
{
	m_speed = 150.f;

	m_texture.loadFromFile("Media/Textures/mario_right.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(x, y);
}

Player::~Player()
{
}

void Player::Jump(sf::Time elapsedTime) {
	if (!this->IsOnLadder()) {
		sf::Vector2f movement(0.f, 0.f);
		movement.y -= m_speed;
		this->m_sprite.move(movement * elapsedTime.asSeconds());
	}
}

bool Player::GoDown(sf::Time elapsedTime)
{
	if (this->IsAboveOrOnLadder() || OnVoid())
	{
		sf::Vector2f movement(0.f, 0.f);
		movement.y += m_speed;
		this->m_sprite.move(movement * elapsedTime.asSeconds());
		return true;
	}
	return false;

}

void Player::TryToEatCoin()
{
	for (std::shared_ptr<Entity> entity : LevelFactory::GetLevel()->mCoins)
	{
		sf::FloatRect fr = entity->m_sprite.getGlobalBounds();
		if (this->m_sprite.getGlobalBounds().intersects(fr))
		{
			entity->m_enabled = false;
			break;
		}
	}
}

bool Player::HasEatenAllCoins()
{
	if (LevelFactory::GetLevel()->GetCoinsEaten() == LevelFactory::GetLevel()->mCoins.size())
	{
		return true;
	}
	return false;
}

bool Player::HasCollidedEnemy()
{
	for (std::shared_ptr<Entity> entity : LevelFactory::GetLevel()->mEnemies)
	{
		sf::FloatRect fr = entity->m_sprite.getGlobalBounds();
		if (this->m_sprite.getGlobalBounds().intersects(fr))
		{
			return true;
		}
	}
	return false;
}

void Player::GoLeft(sf::Time elapsedTime)
{
	m_texture.loadFromFile(m_leftTexturePath);
	m_sprite.setTexture(m_texture);
	Entity::GoLeft(elapsedTime);
}

void Player::GoRight(sf::Time elapsedTime)
{
	m_texture.loadFromFile(m_rightTexturePath);
	m_sprite.setTexture(m_texture);
	Entity::GoRight(elapsedTime);
}

bool Player::GoUp(sf::Time elapsedTime)
{
	m_texture.loadFromFile(m_upTexturePath);
	m_sprite.setTexture(m_texture);
	return Entity::GoUp(elapsedTime); 
}

void Player::Dies()
{	
	if (mDiesBuffer.loadFromFile(m_deathSoundPath))
	{
		mDeathSound.setBuffer(mDiesBuffer);
		mDeathSound.play();
		mDeathSound.setPlayingOffset(sf::seconds(2.f));
	}
}

void Player::Wins()
{
	if (mWinsBuffer.loadFromFile(m_win1SoundPath))
	{
		mWin1Sound.setBuffer(mWinsBuffer);
		mWin1Sound.play();
		mWin1Sound.setPlayingOffset(sf::seconds(2.f));
	}
}



