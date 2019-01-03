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
	void GoLeft(sf::Time elapsedTime) override; 
	void GoRight(sf::Time elapsedTime) override; 
	bool GoUp(sf::Time elapsedTime) override; 

protected:
	std::string m_imagePath = "Media/Textures/mario_right.png";
	std::string m_rightTexturePath = "Media/Textures/mario_right.png";
	std::string m_leftTexturePath = "Media/Textures/mario_left.png";
	std::string m_upTexturePath = "Media/Textures/mario_back.png";
	

};

