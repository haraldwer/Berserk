#include "PineTree.h"

PineTree::PineTree()
{
}

PineTree::~PineTree()
{
}

void PineTree::Init()
{
	sf::Sprite tempSprite = SpriteLib::GetSprite(mySpriteName);
	myWCentering = tempSprite.getTextureRect().width / 4;
	myHCentering = tempSprite.getTextureRect().height / 2 * 0.9f;
	myCollider.setPosition(myX, myY);
	myCollider.setSize(sf::Vector2f(tempSprite.getTextureRect().width/4, tempSprite.getTextureRect().height/4));
	myCollider.setOrigin(myCollider.getSize().x - myWCentering, myCollider.getSize().y - myHCentering);
	myIsSolid = true;
}