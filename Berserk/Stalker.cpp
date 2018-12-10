#include "Stalker.h"
#include "Game.h"
#include "Math.h"
#include <cmath>

void Stalker::Init()
{
	myMoveSpd = 3;
	sf::Sprite tempSprite = SpriteLib::GetSprite(mySpriteName);
	myWCentering = tempSprite.getTextureRect().width / 2;
	myHCentering = tempSprite.getTextureRect().height / 2;
	myCollider.setPosition(myX, myY);
	myCollider.setSize(sf::Vector2f(tempSprite.getTextureRect().width, tempSprite.getTextureRect().height));
	myCollider.setOrigin(myHCentering, myWCentering);
	myIsEnemy = true;
}

void Stalker::Update()
{
	InstanceBase* p = Game::FindInstance(Game::player);
	if (p != nullptr)
	{
		float dir = Math::PointDirection(myX, myY, p->myX, p->myY);
		myHSpd = cos(dir)*myMoveSpd;
		myVSpd = sin(dir)*myMoveSpd;
	}

	#pragma region Collisions
	// Collisions
	// Horizontal
	myCollider.setPosition(myX + myHSpd, myY);
	InstanceBase* it = Game::InstanceCollision(myID, Game::crate);
	if (it != nullptr)
	{
		myHSpd = 0;
	}

	// Vertical
	myCollider.setPosition(myX, myY + myVSpd);
	it = Game::InstanceCollision(dynamic_cast<InstanceBase*>(this), Game::crate);
	if (it != nullptr)
	{
		myVSpd = 0;
	}

	// Multiple direction check
	myCollider.setPosition(myX + myHSpd, myY + myVSpd);
	it = Game::InstanceCollision(dynamic_cast<InstanceBase*>(this), Game::crate);
	if (it != nullptr)
	{
		myHSpd = 0;
	}
	myCollider.setPosition(myX, myY); // Reset collider position
	#pragma endregion
}

Stalker::Stalker()
{
}

Stalker::~Stalker()
{
}
