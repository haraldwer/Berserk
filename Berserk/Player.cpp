#include "pch.h"
#include "Player.h"
#include "arrow.h"
#include "Input.h"
#include "Math.h"
#include <cmath>

Player::Player() { }

Player::~Player() { }

void Player::Init()
{
	myAttackTimer = 0;
	myAttackCD = 0;
	myMoveAcc = 0.05f;
	myMoveFric = 0.85f; 

	mySwordDist = -50;
	mySwordDefaultDist = (int)mySwordDist;
	mySwordExtendedDist = -100;
	mySwordSwingSpd = 0.2f;
	mySwordSwingExtSpd = 0.1f;
	mySwordSwingMoveSpd = 0.8f;
	mySwordExtendSpd = 0.3f;

	baseSprite = mySpriteName;
	currentAnim = idle;
	subImg = 0;

	myViewSpd = 0.05f;

	myHP = 3; // Temp variables

	// Creating and storing collider so that we dont need to recreate each frame
	sf::Sprite tempSprite = SpriteLib::GetSprite(mySpriteName);
	myWCentering = tempSprite.getTextureRect().width/2;
	myHCentering = tempSprite.getTextureRect().height/2;
	myCollider.setPosition(myX, myY);
	myCollider.setSize((const sf::Vector2f) sf::Vector2f(tempSprite.getTextureRect().width, tempSprite.getTextureRect().height));
	myCollider.setOrigin(myWCentering, myHCentering);
	mySword = dynamic_cast<Sword*>(Game::AddInstance(Game::sword, "basicSword", myX, myY, true,false)); // Ugly but functional
	mySavedSword = mySword;
	myBow = dynamic_cast<Bow*>(Game::AddInstance(Game::bow, "bow", myX, myY, true, false)); // Ugly but functional
	mySavedBow = myBow;
	mySwordExtended = false;
	aiming = false;
	mySwordSelectedBool = true;
	myWeaponSwappedBool = false;
	myEHeld = false;
	mySavedBow->mySwappedShow = false;
}

void Player::Update()
{
	#pragma region Movement
	// Movement

	float tempH = ((int)Input::KeyDown('D') - (int)Input::KeyDown('A'))*myMoveAcc;
	float tempV = ((int)Input::KeyDown('S') - (int)Input::KeyDown('W'))*myMoveAcc;
	if (tempH != 0 || tempV != 0)
	{
		float dir = Math::PointDirection(0, 0, tempH, tempV);
		float dist = Math::PointDistance(0, 0, tempH, tempV);
		if (dist > myMoveAcc)
		{
			dist = myMoveAcc;
		}
		myVSpd += sin(dir)*dist;
		myHSpd += cos(dir)*dist;
		currentAnim = running;
	}
	else
	{
		currentAnim = idle;
	}

	myVSpd *= pow(myMoveFric, Time::DeltaTime());
	myHSpd *= pow(myMoveFric, Time::DeltaTime());

	if (Input::KeyDown('F'))
	{
		/*
		myX += myHSpd*3;
		myY += myVSpd*3;
		*/

		myHSpd = (cos(mySword->myDir)*4);
		myVSpd = (sin(mySword->myDir)*4); 

	}

	#pragma endregion

	#pragma region SwordSwing
	if (Input::KeyDown(Input::mbLeft) && mySword != nullptr)
	{
		myVSpd *= pow(mySwordSwingMoveSpd, Time::DeltaTime());
		myHSpd *= pow(mySwordSwingMoveSpd, Time::DeltaTime());
		mySwordDist += (mySwordExtendedDist - mySwordDist)*mySwordExtendSpd*Time::DeltaTime();
		mySwordExtended = true;
	}
	else
	{
		mySwordExtended = false;
		mySwordDist += (mySwordDefaultDist - mySwordDist)*mySwordExtendSpd*Time::DeltaTime();
	}
	#pragma endregion

	#pragma region weaponSelect 
	if (Input::KeyDown('E') && !myWeaponSwappedBool && myEHeld == false)
	{
		mySwordSelectedBool = !mySwordSelectedBool;
		myWeaponSwappedBool = true;
		myEHeld = true;
	}
	
	if (!Input::KeyDown('E'))
	{
		myEHeld = false;
	}

	if (mySwordSelectedBool && myWeaponSwappedBool)
	{
		mySavedBow->mySwappedShow = false;
		mySavedSword->mySwappedShow = true;
		//sword is chosen
		//save the current bow and unequip it
		if (myBow != nullptr)
		{
			mySavedBow = myBow;
		}
		myBow = nullptr;
		mySword = mySavedSword; //requip sword
		myWeaponSwappedBool = false;
	}
	else if(!mySwordSelectedBool && myWeaponSwappedBool)
	{
		//bow is selected
		mySavedBow->mySwappedShow = true;
		mySavedSword->mySwappedShow = false;

		if (mySword != nullptr)
		{
			mySavedSword = mySword; //save the current sword
		}
		mySword = nullptr;
		myBow = mySavedBow;
		myWeaponSwappedBool = false;
	}

#pragma endregion

	#pragma region Collisions
	// Collisions
	// Horizontal
	int lookingfor [2] = {Game::crate, Game::wall}; //ganska stolt �ver denna l�sningen faktiskt!
	for (int i = sizeof(lookingfor) - 1; i >= 0; i--)
	{
		myCollider.setPosition(myX + myHSpd, myY);
		InstanceBase* it = Game::InstanceCollision(myID, (Game::TYPE)lookingfor[i]);
		if (it != nullptr)
		{
			int sign = 1;
			if (!signbit(myHSpd))
			{
				sign = -1;
			}
			while (myHSpd*-sign > 0 && it != nullptr)
			{
				myHSpd += sign;
				myCollider.setPosition(myX + myHSpd, myY);
				it = Game::InstanceCollision(myID, (Game::TYPE)lookingfor[i]);
			}
		}

		// Vertical
		myCollider.setPosition(myX, myY + myVSpd);
		it = Game::InstanceCollision(dynamic_cast<InstanceBase*>(this), (Game::TYPE)lookingfor[i]);
		if (it != nullptr)
		{
			int sign = 1;
			if (!signbit(myVSpd))
			{
				sign = -1;
			}
			while (myVSpd*-sign > 0 && it != nullptr)
			{
				myVSpd += sign;
				myCollider.setPosition(myX, myY + myVSpd);
				it = Game::InstanceCollision(dynamic_cast<InstanceBase*>(this), Game::crate);
			}
		}

		// Multiple direction check
		myCollider.setPosition(myX + myHSpd, myY + myVSpd);
		it = Game::InstanceCollision(dynamic_cast<InstanceBase*>(this), (Game::TYPE)lookingfor[i]);
		if (it != nullptr)
		{
			myHSpd = 0;
		}
		myCollider.setPosition(myX, myY); // Reset collider position
	}
	#pragma endregion

	#pragma region Moving Weapons
	if (myBow != nullptr)
	{
		//move the bow
		myBow->myX = cos((myBow->myDir + 90) / (180 / Math::pi)) * mySwordDist + myX;
		myBow->myY = sin((myBow->myDir + 90) / (180 / Math::pi)) * mySwordDist + myY;
		float newDir = Math::DirDiff(myBow->myDir, Math::RadToDir(Math::PointDirection(myX, myY, Input::GetMouseGlobalX(), Input::GetMouseGlobalY())) + 90);
		myBow->myDir += newDir * Time::DeltaTime();

	}

	if (mySword != nullptr)
	{
		// Might want to move this into sword in order to get proper hitcheck?
		mySword->myX = cos((mySword->myDir + 90) / (180 / Math::pi)) * mySwordDist + myX;
		mySword->myY = sin((mySword->myDir + 90) / (180 / Math::pi)) * mySwordDist + myY;
		float newDir = Math::DirDiff(mySword->myDir, Math::RadToDir(Math::PointDirection(myX, myY, Input::GetMouseGlobalX(), Input::GetMouseGlobalY())) + 90);
		if (mySwordExtended)
		{
			newDir *= mySwordSwingExtSpd;
		}
		else
		{
			newDir *= mySwordSwingSpd;
		}
		mySword->myDir += newDir*Time::DeltaTime();

		// Check if sword is swung and if colliding with enemy and in that case, deal damage.
		if (abs(newDir) >= mySword->mySwingThresh || mySwordExtended)
		{
			for (auto it : Game::InstanceCollisionList(dynamic_cast<InstanceBase*>(mySword), Game::EnemyBase))
			{
				if (it->myType == Game::miniBoss)
				{
					int tepm = 0;

				}
				if ((it->myType != Game::sword) && (it->myType != Game::bow) && (it->myType != Game::arrow))
				{
					dynamic_cast<EnemyBase*>(it)->DealDamage(mySword->myDamage);
					it->myDir *= -1;

				}
				else if (it->myType == Game::sword)
				{
					if(dynamic_cast<Sword*>(it)->myDropped == false) //would look derpy if it effected a dropped sword
					{
						it->myDir += -1.5*newDir;
					}
				}
			}

			for (auto it : Game::InstanceCollisionList(dynamic_cast<InstanceBase*>(mySword), Game::miniBoss))
			{
				if (it->myType == Game::miniBoss)
				{
					dynamic_cast<EnemyBase*>(it)->DealDamage(mySword->myDamage);
					it->myDir *= -1;
					it->myHSpd = cos(it->myDir)*6 * abs(newDir) * 5;
					it->myVSpd = sin(it->myDir)*6 * abs(newDir) * 5;

				}
			}
		}
	}
#pragma endregion

	#pragma region BowControls
	if (Input::KeyDown(Input::mbLeft))
	{
		aiming = true;
		//aim
	}
	else if(aiming)
	{
		if (myBow != nullptr)
		{
			aiming = false;
			//shoot arrow Instanc_create(x,y,arrow); 
			//ADD ARROWS HERE
			InstanceBase* arw = Game::AddInstance(Game::arrow, "arrow", myX, myY, true, false);
			arw->myDir = Math::PointDirection(myX, myY, Input::GetMouseGlobalX(), Input::GetMouseGlobalY());
		}
	}
#pragma endregion

	#pragma region Animations
	// Animations
	/*
	subImg += Time::DeltaTime() / 4;
	switch (currentAnim)
	{
	case idle:
		if (subImg >= 4)
		{
			subImg = 0;
		}
		mySpriteName = baseSprite + "_idle" + std::to_string((int)floor(subImg));
		break;
	case running:
		if (subImg >= 2)
		{
			subImg = 0;
		}
		mySpriteName = baseSprite + "_run" + std::to_string((int)floor(subImg));
		break;
	case attacking:
		mySpriteName = baseSprite + "_attack";
		break;
	}
	*/
	#pragma endregion

#pragma region WeaponPickUp
	
	//minecraft and chill
	if (Input::KeyDown('Q'))
	{
		InstanceBase* it = Game::InstanceCollision(myID, Game::sword);

		if (it!= nullptr && it != mySword)
		{
			if (dynamic_cast<Sword*>(it)->myDropped)
			{
				it->mySpriteName = "crate";
				mySword = dynamic_cast<Sword*>(it);
			}
		}
	}


#pragma endregion
}

void Player::EndUpdate()
{
	InstanceBase::EndUpdate();
	Game::view->move((myX - Game::view->getCenter().x)*myViewSpd*Time::DeltaTime(), (myY - Game::view->getCenter().y)*myViewSpd*Time::DeltaTime());
}

// When the player takes damage. It makes more sense when you call the method from another instance, i promise! xD
void Player::DealDamage(int damage)
{
	EnemyBase::DealDamage(damage);

	// Add some indication that damage has been taken
	//Game::AddInstance(Game::bone, "bone", myX, myY); 
}

void Player::Die()
{
	// Add some cool effect 
	//Game::AddInstance(Game::control, "", 0, 0); 
	
	// Restart game
}
