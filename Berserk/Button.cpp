#include "Button.h"
#include "Game.h"
#include "instanceBase.h"



Button::Button()
{
}


Button::~Button()
{
}

void Button::Init()
{
	sf::Sprite tempSprite = SpriteLib::GetSprite(mySpriteName);
	myWCentering = tempSprite.getTextureRect().width / 2;
	myHCentering = tempSprite.getTextureRect().height / 2;
	myCollider.setPosition(myX, myY);
	myCollider.setSize(sf::Vector2f(tempSprite.getTextureRect().width, tempSprite.getTextureRect().height));
	myCollider.setOrigin(myHCentering, myWCentering);
	pressed = false;
	Permanent = false;
	myNotPressedSpriteNameSave = mySpriteName;
	myPressedSpriteName = "buttonPressed";
}

void Button::Update()
{
	bool tempPressed = false;
	myCollider.getScale();
	InstanceBase* it = Game::InstanceCollision(myID, Game::arrow);
	if(it != nullptr) //WHY DOESNT THIS WORK
	{
		pressed = true;
		tempPressed = true;
	}

	/*

	for (auto it : Game::InstanceCollisionList(myID, Game::player)) //WHY DOESNT THIS WORK
	{
			pressed = true;
			tempPressed = true;
	}

	*/

	if (!Permanent)
	{
		pressed = tempPressed; //if the button is permanent it will have been set to true
	}

	if (pressed)
	{
		mySpriteName = myPressedSpriteName;
	}
	else
	{
		mySpriteName = myNotPressedSpriteNameSave;
	}

}


