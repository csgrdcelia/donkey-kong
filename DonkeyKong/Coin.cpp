#include "pch.h"
#include "Coin.h"
#include "LevelFactory.h"


Coin::Coin()
{
}

Coin::Coin(float x, float y) : Entity(x, y)
{
	UpdateTexture("Media/Textures/coin.png");
	mSprite.setPosition(x, y);
}


Coin::~Coin()
{
}

bool Coin::CollidesLadder(std::vector<std::shared_ptr<Ladder>> mLadders)
{
	for (std::shared_ptr<Entity> entity : mLadders)
	{
		sf::FloatRect fr = entity->mSprite.getGlobalBounds();
		fr.top -= 30; // so Mario can continue to hike when he's on the block
		if (this->mSprite.getGlobalBounds().intersects(fr))
		{
			return true;
			break;
		}
	}
	return false;
}

void Coin::CoinSound()
{
	if (mCoinBuffer.loadFromFile(mCoinSoundPath))
	{
		mCoinSound.setBuffer(mCoinBuffer);
		mCoinSound.play();
		mCoinSound.setPlayingOffset(sf::seconds(2.f));
	}
}