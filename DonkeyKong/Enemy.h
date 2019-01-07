#pragma once
#include "Entity.h"
class Enemy : public Entity
{
public:
	Enemy();
	Enemy(float x, float y);
	~Enemy();

public:
	void Move(sf::Time elapsedTime);

private:
	void GoLeftOrRight(sf::Time elapsedTime);
	void ChangeSideIfOnEdge(sf::Time elapsedTime);
	void GoLeft(sf::Time elapsedTime) override; 
	void GoRight(sf::Time elapsedTime) override; 

private:
	bool IsGoingUp = false;
	bool IsGoingDown = false;
	int frameTimer = 0;

protected: 
	std::string mRightTexturePath = "Media/Textures/enemy_1_right.png"; 
	std::string mLeftTexturePath = "Media/Textures/enemy_2_left.png";
};

