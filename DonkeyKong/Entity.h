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
	bool GoDown(sf::Time elapsedTime);
	bool IsOnLadder();		
	bool IsAboveOrOnLadder();
	bool CollidesBlock();
	bool OnVoid();
	bool IsOutsideOfWindow();

public:
	sf::Sprite m_sprite;
	bool m_enabled = true;
	int m_times = 0;

protected:
	sf::Texture m_texture;

public:
	float	m_speed;
};