#include "PlayerSword.h"
#include "Game.h"

PlayerSword::~PlayerSword()
{
}

void PlayerSword::Init()
{
}

void PlayerSword::Update()
{
	// Check if colliding with enemy and in that case, deal damage.
	for (auto it : Game::InstanceCollisionList(dynamic_cast<InstanceBase*>(this), Game::baseEnemy))
	{
		it->DealDamage(1);
	}
}
