#include "EnemyBase.h"

void EnemyBase::DealDamage(int damage)
{
	myHP -= damage;
	if (myHP < 0)
	{
		Die();
	}
}

void EnemyBase::Die()
{
	// Create some kind of effect here?
	myDestroy = true;
}

EnemyBase::EnemyBase()
{
}

EnemyBase::~EnemyBase()
{
}