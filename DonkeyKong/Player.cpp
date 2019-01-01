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


