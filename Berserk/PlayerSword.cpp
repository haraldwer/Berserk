#include "pch.h"
#include "PlayerSword.h"
#include "Game.h"
#include "Math.h"
#include "Input.h"

PlayerSword::PlayerSword()
{
}

PlayerSword::~PlayerSword()
{
}

void PlayerSword::Init()
{
	// Comment and stuff
}

void PlayerSword::Update()
{
	// Check if colliding with enemy and in that case, deal damage.
	for (auto it : Game::InstanceCollisionList(dynamic_cast<InstanceBase*>(this), Game::baseEnemy))
	{
		it->DealDamage(1);
	}
	
	myDir = Math::PointDirection(0, 0, Input::GetMouseX(), Input::GetMouseY());
}
