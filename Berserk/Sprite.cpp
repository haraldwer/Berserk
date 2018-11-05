#include "pch.h"
#include "Sprite.h"


Sprite::Sprite(std::vector<unsigned char> aSprite, int aWidth, int aHeight)
{
	sprite = aSprite;
	width = aWidth;
	height = aHeight;
}

Sprite::Sprite() { }

Sprite::~Sprite() { }