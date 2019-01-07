#include "pch.h"
#include "Block.h"


Block::Block()
{
}

Block::Block(float x, float y) : Entity(x, y)
{
	mTexture.loadFromFile("Media/Textures/Block.png");
	mSprite.setTexture(mTexture);
	mSprite.setPosition(x, y);
}


Block::~Block()
{
}
