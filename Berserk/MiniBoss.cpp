#include "MiniBoss.h"
#include "Game.h"
#include "Math.h"


//MiniBoss::MiniBoss(){}


MiniBoss::~MiniBoss()
{
}

void MiniBoss::Init()
{
	myHP = 15000;
	sf::Sprite tempSprite = SpriteLib::GetSprite(mySpriteName);
	myWCentering = tempSprite.getTextureRect().width / 2;
	myHCentering = tempSprite.getTextureRect().height / 2;
	myCollider.setPosition(myX, myY);
	myCollider.setSize(sf::Vector2f(tempSprite.getTextureRect().width, tempSprite.getTextureRect().height));
	myCollider.setOrigin(myHCentering, myWCentering);

	mySword = dynamic_cast<Sword*>(Game::AddInstance(Game::sword, "basicSword", myX, myY, true, false)); // Ugly but functional
	mySword->myIsEnemy = true;
	mySword->mySwappedShow = true; //in order to show 

	mySwordDist = -50;
	mySwordDefaultDist = (int)mySwordDist;
	mySwordExtendedDist = -100;
	mySwordSwingSpd = 0.2f;
	mySwordSwingExtSpd = 0.13f;
	mySwordSwingMoveSpd = 0.8f;
	mySwordExtendSpd = 0.3f;
	myAttackState = spin;
	TESTSpin = 0;
	myMoveSpd = 3;
	myDefualtStateChangerTime = 1 * 60 * 60 * Time::DeltaTime();
	myStateChangerTimer = 0;

	myDefaultStabTime = 3 * 60 * Time::DeltaTime();
	mystabTimer = 0;
	myStabExtensionTime = 2 * 60;

	mySwordSwingChargeTimer = 5 * 60;


}

void MiniBoss::Update()
{
	if (!myDestroy)
	{
		InstanceBase* p = Game::FindInstance(Game::player);
		if (p != nullptr)
		{
			float dir = Math::PointDirection(myX, myY, p->myX, p->myY);
			myDir = dir; //testing this XXXXXXXXXX
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


#pragma region SwordSwingwwd

		myStateChangerTimer++;
		if (myDefualtStateChangerTime < myStateChangerTimer)
		{
			myAttackState = (bossAttackState)(rand() % offblanace); //NOTE WE NEED T O KEEP OFFBALANCE AS THE LAST ONE TO USE THIS SYSTEM!!!!!!!!
			myStateChangerTimer = 0;
			TESTSpin = 0;
			mystabTimer = 0;

		}

		int tempdist = 0;
		if (p != nullptr)
		{
			tempdist = sqrt((myX - p->myX)*(myX - p->myX) + (myY - p->myY)*(myY - p->myY));
		}

		if (myAttackState == spin)
		{
			if (TESTSpin < 360 * 3)
			{
				TESTSpin += 0.6f;
			}
		}
		else if (myAttackState == stab)
		{
			mystabTimer++;
			if (myDefaultStabTime < mystabTimer) //timer is done extend sword
			{
				mySwordExtended = true;
			}
			else if (myDefaultStabTime + myStabExtensionTime < mystabTimer) //you have extended your sword for long enough, retract it
			{
				mySwordExtended = false;
				mystabTimer = 0; //restart the timer
			}
		}
		else if (myAttackState == poke)
		{
			//right now its just copied swing code
			if (myStateChangerTimer < mySwordSwingChargeTimer)
			{
				mySwordSwingDir = 140;
			}
			else
			{
				mySwordSwingDir = 0;
			}
		}
		else if (myAttackState == swing)
		{
			if (myStateChangerTimer < mySwordSwingChargeTimer)
			{
				mySwordSwingDir = 140;
			}
			else
			{
				mySwordSwingDir = 0;
			}
		}
		else if (myAttackState == bow)
		{
			InstanceBase* arw = Game::AddInstance(Game::arrow, "arrow", myX, myY, true, false);
			arw->myDir = myDir; //TESTING THIS....   //Math::PointDirection(myX, myY, Input::GetMouseGlobalX(), Input::GetMouseGlobalY());
			arw->myIsEnemy = true;
			myStateChangerTimer = myDefualtStateChangerTime;
		}
		else if (sizeUp == myAttackState)
		{
			myHScale *= 2;
			myVScale *= 2;
			myStateChangerTimer = myDefualtStateChangerTime;
		}

		if (tempdist < 340 && mySword != nullptr && myAttackState != stab)
		{
			myVSpd *= pow(mySwordSwingMoveSpd, Time::DeltaTime()); //reduces movement speed
			myHSpd *= pow(mySwordSwingMoveSpd, Time::DeltaTime());
			mySwordDist += (mySwordExtendedDist - mySwordDist)*mySwordExtendSpd*Time::DeltaTime(); //weapon extended 
			mySwordExtended = true;
		}
		else if (tempdist < 340 && mySword != nullptr && myAttackState == stab)
		{
			if (mySwordExtended)
			{
				mySwordDist += (mySwordExtendedDist - mySwordDist)*mySwordExtendSpd*Time::DeltaTime(); //weapon extended 
			}
			else
			{
				mySwordDist += (mySwordDefaultDist - mySwordDist)*mySwordExtendSpd*Time::DeltaTime();
			}

		}
		else
		{
			mySwordExtended = false;
			mySwordDist += (mySwordDefaultDist - mySwordDist)*mySwordExtendSpd*Time::DeltaTime();
		}

		if (mySword != nullptr)
		{
			// Might want to move this into sword in order to get proper hitcheck?
			mySword->myX = cos((mySword->myDir + 90) / (180 / Math::pi)) * mySwordDist + myX; //calculates the new x and y positions for the sword
			mySword->myY = sin((mySword->myDir + 90) / (180 / Math::pi)) * mySwordDist + myY;
			float newDir = Math::DirDiff(mySword->myDir, Math::RadToDir(Math::PointDirection(myX, myY, p->myX, p->myY)) + 90 + TESTSpin + mySwordSwingDir);

			if (mySwordExtended)
			{
				newDir *= mySwordSwingExtSpd;
			}
			else
			{
				newDir *= mySwordSwingSpd;
			}
			mySword->myDir += newDir * Time::DeltaTime();

			// Check if sword is swung and if colliding with enemy and in that case, deal damage.
			if (abs(newDir) >= mySword->mySwingThresh || mySwordExtended)
			{

				for (auto it : Game::InstanceCollisionList(dynamic_cast<InstanceBase*>(mySword), Game::player))
				{
					if (it->myType == Game::player) //super mega ful lösning, men den bör fungera!
					{
						dynamic_cast<EnemyBase*>(it)->DealDamage(mySword->myDamage);
					}
				}

			}
		}



#pragma endregion

	}

}
