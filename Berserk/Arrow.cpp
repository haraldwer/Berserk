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
	myCollider.setSize(sf::Vector2f(tempSprite.getTextureRect().width*0.6, tempSprite.getTextureRect().height*0.6));
	myCollider.setOrigin(myHCentering*0.6, myWCentering*0.6);
//	myDir = myBowOrigin->myDir;
	myallowedLifeTime = 60 * 60 * 7;
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
		if(it->myType != Game::sword) //det �r inte ett sv�rd
		{
			dynamic_cast<EnemyBase*>(it)->DealDamage(myDamage);
		}
			myDestroy = true;
		
		if (it->myType == Game::sword) //det �r ett sv�rd
		{//som �r droppat
			if(dynamic_cast<Sword*>(it)->myDropped) //super mega ful l�sning, men den b�r fungera!
			{
				myDestroy = false;
			}
		}
	}
	
}

void Arrow::EndDraw(sf::RenderWindow * window)
{
}
