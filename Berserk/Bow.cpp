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
	mySwappedShow = true;
	myDamage = 1;
}

void Bow::Update()
{


}

void Bow::Draw(sf::RenderWindow* window, bool editorOpen)
{
	if(mySwappedShow)
	{
		if (mySpriteName != "")
		{
			// Draw sprite
			sf::Sprite sprite = SpriteLib::GetSprite(mySpriteName);
			sprite.setPosition(myX, myY);
			sprite.setOrigin(myWCentering, myHCentering);
			sprite.setRotation(myDir);
			//window->draw(myCollider);
			window->draw(sprite);
		}
		else if (editorOpen)
		{
			// Draw sprite
			sf::Sprite sprite = SpriteLib::GetSprite("unknown");
			sprite.setPosition(myX, myY);
			sprite.setOrigin(myWCentering, myHCentering);
			sprite.setRotation(myDir);
			window->draw(sprite);
		}
	}
}

void Bow::EndDraw(sf::RenderWindow* window)
{
	if (dropped)
	{
		sf::Text text;
		text.setFillColor(sf::Color::Black);
		text.setString("This is a test");
		text.setCharacterSize(24);
		text.setFont(Game::font);
		window->draw(text);
	}
}
