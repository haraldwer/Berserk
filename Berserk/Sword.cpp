#include "pch.h"
#include "Sword.h"
#include "Game.h"
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
	dropped = false;
}

void Sword::Update()
{
	
	// Check if colliding with enemy and in that case, deal damage.
	for (auto it : Game::InstanceCollisionList(dynamic_cast<InstanceBase*>(this), Game::EnemyBase))
	{
		dynamic_cast<EnemyBase*>(it)->DealDamage(1);
	}
}

void Sword::EndDraw(sf::RenderWindow* window)
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