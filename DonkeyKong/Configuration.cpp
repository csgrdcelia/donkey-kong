#include "pch.h"
#include "Configuration.h"
#include "Player.h"


Configuration::Configuration()
{
}


Configuration::~Configuration()
{
}

Player Configuration::CreatePlayer()
{
	sf::Texture *texture = new sf::Texture();
	sf::Sprite	sprite;
	sf::Vector2f position;
	(*texture).loadFromFile("Media/Textures/mario_right.png");
	sprite.setTexture(*texture);
	sprite.setPosition(170.f, 550 - (*texture).getSize().y);

	Player player;
	player.m_sprite = sprite;
	player.m_size = (*texture).getSize();
	player.m_position = sprite.getPosition();

	return player;
}
