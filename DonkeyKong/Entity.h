#pragma once


class Entity
{

protected:
	Entity();
	Entity(float x, float y);
public:
	Entity(float x, float y, std::string pathToPNG);

public:
	virtual ~Entity() { };

public:
	virtual void GoRight(sf::Time elapsedTime);
	virtual void GoLeft(sf::Time elapsedTime);
	virtual bool GoUp(sf::Time elapsedTime);
	virtual void UpdateTexture(std::string path);
	bool GoDown(sf::Time elapsedTime);
	bool IsOnLadder();		
	bool IsAboveOrOnLadder();
	bool CollidesBlock();
	bool OnVoid();
	bool IsOutsideOfWindow();

public:
	bool GoesToTheRight = true;
	sf::Sprite mSprite;
	bool mEnabled = true;
	int mTimes = 0;

protected:
	sf::Texture mTexture;

public:
	float	m_speed;
};