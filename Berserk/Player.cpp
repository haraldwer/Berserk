#include "pch.h"
#include "Player.h"
#include "Input.h"
#include "Math.h"
#include <cmath>
#include "Game.h"

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

	baseSprite = mySpriteName;
	currentAnim = idle;
	subImg = 0;

	myHP = 3; // Temp variables

	// Creating and storing collider so that we dont need to recreate each frame
	sf::Sprite tempSprite = SpriteLib::GetSprite(mySpriteName);
	myCollider.setPosition(myX, myY);
	myCollider.setSize(sf::Vector2f(tempSprite.getTextureRect().width, tempSprite.getTextureRect().height));

	mySword = Game::AddInstance(Game::playerSword, "basicSword", myX, myY);
}

void Player::Update()
{
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
	myVSpd *= pow(myMoveFric, Time::DeltaTime());//myMoveFric*Time::DeltaTime();
	myHSpd *= pow(myMoveFric, Time::DeltaTime());//myMoveFric*Time::DeltaTime();

	

	// Collisions
	// Horizontal
	myCollider.setPosition(myX + myHSpd, myY);
	InstanceBase* it = Game::InstanceCollision(dynamic_cast<InstanceBase*>(this), Game::crate);
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
			it = Game::InstanceCollision(dynamic_cast<InstanceBase*>(this), Game::crate);
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

	mySword->myX = myX;
	mySword->myY = myY - 50;

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
}

// When the player takes damage. It makes more sense when you call the method from another instance, i promise! xD
void Player::DealDamage(int damage)
{
	InstanceBase::DealDamage(damage);

	// Add some indication that damage has been taken
	//Game::AddInstance(Game::bone, "bone", myX, myY); 
}

void Player::Die()
{
	// Add some cool effect 
	//Game::AddInstance(Game::control, "", 0, 0); 
	
	// Restart game
}
