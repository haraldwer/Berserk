#include "Player.h"
#include "Time.h"
#include "Input.h"
#include "Math.h"

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
	myMoveAcc = 0.1;
	myMoveFric = 0.965;

	baseSprite = mySpriteName;
	currentAnim = idle;
	subImg = 0;

	myHP = 3; // Temp variables
}

void Player::BeginUpdate()
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
	myVSpd *= myMoveFric;
	myHSpd *= myMoveFric;

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
