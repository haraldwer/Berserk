#include "Crate.h"

Crate::~Crate()
{
}

void Crate::Init()
{
	myHP = 0;
	sf::Sprite tempSprite = SpriteLib::GetSprite(mySpriteName);
	myCollider.setPosition(myX, myY);
	myCollider.setSize(sf::Vector2f(tempSprite.getTextureRect().width, tempSprite.getTextureRect().height));
	myIsSolid = true;
}