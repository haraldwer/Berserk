#include "Arrow.h"
#include "Bow.h"
#include "pch.h"
#include "Game.h"
#include "Input.h"
#include "Math.h"
#include "Sword.h"

Arrow::Arrow()
{

}

Arrow::~Arrow()
{

}

void Arrow::Init()
{

	Game::SetInstanceDepth(myID, 1);
	sf::Sprite tempSprite = SpriteLib::GetSprite(mySpriteName);
	myWCentering = tempSprite.getTextureRect().width / 2;
	myHCentering = tempSprite.getTextureRect().height / 2;
	myCollider.setPosition(myX, myY);
	myCollider.setSize(sf::Vector2f(tempSprite.getTextureRect().width, tempSprite.getTextureRect().height));
	myCollider.setOrigin(myHCentering, myWCentering);
//	myDir = myBowOrigin->myDir;
	myallowedLifeTime = 60 * 60 * 6;
	mySpeed = 4;
	myDamage = 2;
}

void Arrow::Update()
{
	myLifeTimer++;
	if(myLifeTimer > myallowedLifeTime)
	{
		myDestroy = true;
	}
	
	myHSpd = cos(myDir)*mySpeed;
	myVSpd = sin(myDir)*mySpeed;
	//float newDir = Math::DirDiff(myDir, Math::RadToDir(Math::PointDirection(myX, myY, myX, myY)) + 90);
	//myDir += newDir * Time::DeltaTime();

	// Check if sword is swung and if colliding with enemy and in that case, deal damage.

	for (auto it : Game::InstanceCollisionList(this,Game::EnemyBase))
	{
		if(((it->myType != Game::sword) && (it->myType != Game::bow) && (it->myType != Game::arrow) && it->myIsEnemy != myIsEnemy)) //det är inte ett svärd eller bow
		{
			dynamic_cast<EnemyBase*>(it)->DealDamage(myDamage);
			myDestroy = true;
		}
		
		if (it->myType == Game::sword) //det är ett svärd
		{//som är droppat
			if(dynamic_cast<Sword*>(it)->myDropped) //super mega ful lösning, men den bör fungera!
			{
				myDestroy = false;
			}
		}
	}
	
}

void Arrow::EndDraw(sf::RenderWindow * window)
{
}
