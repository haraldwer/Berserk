#include "Crate.h"

Crate::~Crate()
{
}

void Crate::Init()
{
	myHP = 0;
	sf::Sprite tempSprite = SpriteLib::GetSprite(mySpriteName);
	myWCentering = tempSprite.getTextureRect().width / 2;
	myHCentering = tempSprite.getTextureRect().height / 2;
	myCollider.setPosition(myX, myY);
	myCollider.setSize(sf::Vector2f(tempSprite.getTextureRect().width, tempSprite.getTextureRect().height));
	myCollider.setOrigin(myHCentering, myWCentering);
	myIsSolid = true;
	myIsEnemy = true;
}