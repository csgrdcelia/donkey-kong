#include "pch.h"
#include "Coin.h"
#include "LevelFactory.h"


Coin::Coin()
{
}

Coin::Coin(float x, float y) : Entity(x, y)
{
	m_texture.loadFromFile("Media/Textures/coin.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(x, y);
}


Coin::~Coin()
{
}

bool Coin::CollidesLadder()
{
	for (std::shared_ptr<Entity> entity : LevelFactory::GetLevel()->mLadders)
	{
		sf::FloatRect fr = entity->m_sprite.getGlobalBounds();
		fr.top -= 30; // so Mario can continue to hike when he's on the block
		if (this->m_sprite.getGlobalBounds().intersects(fr))
		{
			return true;
			break;
		}
	}
	return false;
}