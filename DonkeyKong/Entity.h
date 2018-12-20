#pragma once


class Entity
{
public:
	Entity() { };
	~Entity() { };

public:
	void GoRight(sf::Time elapsedTime);
	void GoLeft(sf::Time elapsedTime);
	bool GoUp(sf::Time elapsedTime);
	bool GoDown(sf::Time elapsedTime);
	bool IsOnLadder();		
	bool IsAboveOrOnLadder();
	bool CollidesBlock();
	bool OnVoid();
	bool IsOutsideOfWindow();

public:
	sf::Sprite m_sprite;
	sf::Vector2u m_size;
	sf::Vector2f m_position;
	bool m_enabled = true;

	// Enemy only
	bool m_bLeftToRight = true;
	int m_times = 0;

public:
	float	Speed;
};