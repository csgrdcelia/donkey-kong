#include "pch.h"
#include "Ladder.h"


Ladder::Ladder()
{
}

Ladder::Ladder(float x, float y) : Entity(x, y)
{
	m_texture.loadFromFile("Media/Textures/Echelle.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(x, y);
}


Ladder::~Ladder()
{
}
