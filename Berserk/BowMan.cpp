#include "BowMan.h"
#include "Game.h"
#include "Math.h"
#include <cmath>


BowMan::BowMan()
{
}


BowMan::~BowMan()
{
}

void BowMan::Update()
{
	if (!myDestroy)
	{
		InstanceBase* p = Game::FindInstance(Game::player);
		if (p != nullptr)
		{
			float dir = Math::PointDirection(myX, myY, p->myX, p->myY);

			myHSpd = cos(dir)*myMoveSpd;
			myVSpd = sin(dir)*myMoveSpd;

			if (Math::PointDistance(myX, myY, p->myX, p->myY) < 200)
			{
				myHSpd = -cos(dir)*myMoveSpd;
				myVSpd = -sin(dir)*myMoveSpd;
			}
			else if (Math::PointDistance(myX, myY, p->myX, p->myY) < 250)
			{
				myHSpd = 0;
				myVSpd = 0;
			}

			myBow->myX = myX;
			myBow->myY = myY;


			myShootingTimer++;
			if (myShootingTimer > myShootingMaxTime)
			{
				myShootingTimer = 0;
				
				InstanceBase* arw = Game::AddInstance(Game::arrow, "arrow", myX, myY, true, false);
				arw->myDir = dir;//Math::PointDirection(myX, myY, Input::GetMouseGlobalX(), Input::GetMouseGlobalY());
				arw->myIsEnemy = true;
			}
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

}

void BowMan::Init()
{
	myMoveSpd = 3;
	sf::Sprite tempSprite = SpriteLib::GetSprite(mySpriteName);
	myWCentering = tempSprite.getTextureRect().width / 2;
	myHCentering = tempSprite.getTextureRect().height / 2;
	myCollider.setPosition(myX, myY);
	myCollider.setSize(sf::Vector2f(tempSprite.getTextureRect().width, tempSprite.getTextureRect().height));
	myCollider.setOrigin(myHCentering, myWCentering);
	myIsEnemy = true;
	myShootingTimer = 0;
	myShootingMaxTime = 8 * 60;

	myBow = dynamic_cast<Bow*>(Game::AddInstance(Game::bow, "bow", myX, myY, true, false)); // Ugly but functional
	myBow->myIsEnemy = true;
	myBow->mySwappedShow = true; //in order to show 
}
