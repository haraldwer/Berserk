#include "Door.h"

void Door::Init()
{
	sf::Sprite tempSprite = SpriteLib::GetSprite(mySpriteName);
	myWCentering = tempSprite.getTextureRect().width / 2;
	myHCentering = tempSprite.getTextureRect().height * 0.9f;
	myCollider.setPosition(myX, myY);
	myCollider.setSize(sf::Vector2f(tempSprite.getTextureRect().width, tempSprite.getTextureRect().height));
	myOpened = false;
}

void Door::Update()
{

}

Door::Door()
{
}


Door::~Door()
{
}
