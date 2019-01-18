#pragma once
#include "pch.h"
#include "Entity.h"
#include <SFML/Audio.hpp>

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
	void Jump(sf::Time elapsedTime);
	void Dies(); 
	void Wins();
	void GravityHandle();

public:
	bool mIsJumping = false;
	int cptJump = 0;
	int cptFall = 10;
	int cptFly = 0;

private: 
	sf::SoundBuffer mDiesBuffer; 
	sf::SoundBuffer mWinsBuffer;
	sf::Sound mDeathSound; 
	sf::Sound mWin1Sound;

protected:
	std::string mImagePath = "Media/Textures/mario_right.png";
	std::string mRightTexturePath = "Media/Textures/mario_right.png";
	std::string mleftTexturePath = "Media/Textures/mario_left.png";
	std::string mUpTexturePath = "Media/Textures/mario_back.png";
	std::string mRightJumpTexturePath = "Media/Textures/mario_jump_right.png";
	std::string mLeftJumpTexturePath = "Media/Textures/mario_jump_left.png";
	std::string mDeathSoundPath = "Media/Sounds/death.wav"; 
	std::string mWin1SoundPath = "Media/Sounds/win1.wav";
};

