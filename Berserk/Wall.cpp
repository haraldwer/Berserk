#include "Wall.h"

Wall::~Wall()
{
}


Wall::Wall()
{
}

void Wall::Init()
{
	sf::Sprite tempSprite = SpriteLib::GetSprite(mySpriteName);
	myCollider.setPosition(myX, myY);
	myCollider.setSize(sf::Vector2f(tempSprite.getTextureRect().width, tempSprite.getTextureRect().height));
	myIsSolid = true;
}


