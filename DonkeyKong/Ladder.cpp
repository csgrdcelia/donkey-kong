#include "pch.h"
#include "Ladder.h"


Ladder::Ladder()
{
}

Ladder::Ladder(float x, float y) : Entity(x, y)
{
	UpdateTexture("Media/Textures/Echelle.png");
	mSprite.setPosition(x, y);
}


Ladder::~Ladder()
{
}
