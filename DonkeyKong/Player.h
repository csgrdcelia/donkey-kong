#pragma once
#include "pch.h"
#include "Entity.h"

class Player : public Entity
{
public:
	Player(float x, float y);
	virtual ~Player();
	

public:
	void TryToEatCoin();
	bool HasEatenAllCoins();
	bool HasCollidedEnemy();
	bool GoDown(sf::Time elapsedTime);

protected:
	std::string m_imagePath = "Media/Textures/mario_right.png";
	


	

};

