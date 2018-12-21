#include "Bow.h"
#include "pch.h"
#include "Game.h"
#include <iostream>


Bow::~Bow()
{
}

void Bow::Init()
{
	Game::SetInstanceDepth(myID, 1);
	sf::Sprite tempSprite = SpriteLib::GetSprite(mySpriteName);
	myWCentering = tempSprite.getTextureRect().width / 2;
	myHCentering = tempSprite.getTextureRect().height / 2;
	myCollider.setPosition(myX, myY);
	myCollider.setSize(sf::Vector2f(tempSprite.getTextureRect().width*0.6, tempSprite.getTextureRect().height*0.6));
	myCollider.setOrigin(myHCentering*1, myWCentering*1);
	dropped = false;
	myDamage = 1;
}

void Bow::Update()
{


}

void Bow::EndDraw(sf::RenderWindow* window)
{
	if (dropped)
	{
		sf::Text text;
		text.setString("This is a test");
		text.setCharacterSize(24);
		text.setFont(Game::font);
		window->draw(text);
	}
}
