#include "pch.h"
#include "Block.h"


Block::Block()
{
}

Block::Block(float x, float y) : Entity(x, y)
{
	m_texture.loadFromFile("Media/Textures/Block.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(x, y);
}


Block::~Block()
{
}
