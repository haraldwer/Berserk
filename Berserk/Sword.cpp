#include "pch.h"
#include "Sword.h"
#include "Game.h"
#include "Input.h"
#include "Player.h"
#include <iostream>

Sword::~Sword()
{
}

void Sword::Init()
{
	Game::SetInstanceDepth(myID, 1);
	sf::Sprite tempSprite = SpriteLib::GetSprite(mySpriteName);
	myWCentering = tempSprite.getTextureRect().width / 2;
	myHCentering = tempSprite.getTextureRect().height / 2;
	myCollider.setPosition(myX, myY);
	myCollider.setSize(sf::Vector2f(tempSprite.getTextureRect().width*0.6, tempSprite.getTextureRect().height*0.6));
	myCollider.setOrigin(myHCentering*0.6, myWCentering*0.6);
	myDropped = false;
	myDamage = 1;
	mySwingThresh = 0;
	mySwappedShow = false;
}

void Sword::Update()
{
#pragma region WeaponPickUp

	//minecraft and chill
	if (myDropped)
	{
		if (Input::KeyDown('Q'))
		{
			InstanceBase* it = Game::InstanceCollision(myID, Game::player);

			if (it != nullptr)
			{
				if (dynamic_cast<Player*>(it))
				{
				//	mySpriteName = "crate"; //debug
				//	dynamic_cast<Player*>(it)->mySword->myDropped = true; //drop the players current weapon 
					dynamic_cast<Player*>(it)->mySword->myDestroy = true; //drop the players current weapon 
					myDropped = false; //make this new weapon not dropped anymore
					dynamic_cast<Player*>(it)->mySword = this; //equip the new weapon
					dynamic_cast<Player*>(it)->mySavedSword = this;
				
				}
			}
		}
	}


#pragma endregion
}

void Sword::Draw(sf::RenderWindow* window, bool editorOpen)
{
	if (mySwappedShow)
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


void Sword::EndDraw(sf::RenderWindow* window)
{
	if (myDropped)
	{
		sf::Text text;
		text.setFillColor(sf::Color::Black);
		text.setPosition(myX,myY-30);
		text.setString("This is a test");
		text.setCharacterSize(24);
		text.setFont(Game::font);
		window->draw(text);
	}
}