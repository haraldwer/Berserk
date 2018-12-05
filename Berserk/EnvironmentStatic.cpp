#include "EnvironmentStatic.h"



EnvironmentStatic::EnvironmentStatic()
{
}


EnvironmentStatic::~EnvironmentStatic()
{
}

void EnvironmentStatic::Init()
{
	sf::Sprite tempSprite = SpriteLib::GetSprite(mySpriteName);
	myWCentering = tempSprite.getTextureRect().width / 2;
	myHCentering = tempSprite.getTextureRect().height * 0.9f;

}
