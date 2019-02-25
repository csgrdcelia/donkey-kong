#pragma once
#include "Entity.h"
#include "Ladder.h"
#include <SFML/Audio.hpp>

class Coin : public Entity
{
public:
	Coin();
	Coin(float x, float y);
	virtual ~Coin();

private:
	sf::SoundBuffer mCoinBuffer;
	sf::Sound mCoinSound;
	std::string mCoinSoundPath = "Media/Sounds/coin.wav";
public:
	bool CollidesLadder(std::vector<std::shared_ptr<Ladder>> mLadders);
	void CoinSound();
};

