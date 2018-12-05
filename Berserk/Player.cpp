#include "pch.h"
#include "Player.h"
#include "Input.h"
#include "Math.h"
#include <cmath>

Player::Player()
{
}

Player::~Player()
{
}

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
	myCollider.setOrigin(myHCentering, myWCentering);
	mySword = Game::AddInstance(Game::sword, "basicSword", myX, myY, true);
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
	#pragma endregion

	#pragma region SwordSwing
	if (Input::KeyDown(Input::mbLeft))
	{
		myVSpd *= pow(mySwordSwingMoveSpd, Time::DeltaTime());
		myHSpd *= pow(mySwordSwingMoveSpd, Time::DeltaTime());
		mySwordDist += (mySwordExtendedDist - mySwordDist)*mySwordExtendSpd*Time::DeltaTime();
	}
	else
	{
		mySwordDist += (mySwordDefaultDist - mySwordDist)*mySwordExtendSpd*Time::DeltaTime();
	}
	#pragma endregion

	#pragma region Collisions
	// Collisions
	// Horizontal
	myCollider.setPosition(myX + myHSpd, myY);
	InstanceBase* it = Game::InstanceCollision(myID, Game::crate);
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
			it = Game::InstanceCollision(myID, Game::crate);
		}
	}

	// Vertical
	myCollider.setPosition(myX, myY + myVSpd);
	it = Game::InstanceCollision(dynamic_cast<InstanceBase*>(this), Game::crate);
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
	it = Game::InstanceCollision(dynamic_cast<InstanceBase*>(this), Game::crate);
	if (it != nullptr)
	{
		myHSpd = 0;
	}
	myCollider.setPosition(myX, myY); // Reset collider position
	#pragma endregion

	mySword->myX = cos((mySword->myDir + 90) / (180 / Math::pi)) * mySwordDist + myX;
	mySword->myY = sin((mySword->myDir + 90) / (180 / Math::pi)) * mySwordDist + myY;
	mySword->myDir += Math::DirDiff(mySword->myDir, Math::RadToDir(Math::PointDirection(myX, myY, Input::GetMouseGlobalX(), Input::GetMouseGlobalY())) + 90)*mySwordSwingSpd*Time::DeltaTime();

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
