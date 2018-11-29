#include "pch.h"
#include "PlayerSword.h"
#include "Game.h"
#include <iostream>

PlayerSword::~PlayerSword()
{
}

void PlayerSword::Init()
{
	Game::SetInstanceDepth(myID, 1);

	// Comment and stuff
	sf::Sprite tempSprite = SpriteLib::GetSprite(mySpriteName);
	myWCentering = tempSprite.getTextureRect().width / 2;
	myHCentering = tempSprite.getTextureRect().height / 2;
	myCollider.setPosition(myX, myY);
	myCollider.setSize(sf::Vector2f(tempSprite.getTextureRect().width, tempSprite.getTextureRect().height));
	myCollider.setOrigin(tempSprite.getTextureRect().width / 2, tempSprite.getTextureRect().height / 2);
}

void PlayerSword::Update()
{
	// Check if colliding with enemy and in that case, deal damage.
	for (auto it : Game::InstanceCollisionList(dynamic_cast<InstanceBase*>(this), Game::EnemyBase))
	{
		dynamic_cast<EnemyBase*>(it)->DealDamage(1);
	}
}
