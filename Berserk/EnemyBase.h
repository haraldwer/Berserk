#ifndef ENEMY_BASE
#define ENEMY_BASE
#include "InstanceBase.h"
class EnemyBase : public InstanceBase
{
	using InstanceBase::InstanceBase;

	public:
		EnemyBase();
		~EnemyBase();
		virtual void DealDamage(int damage);
		virtual void Die();

	int
		myHP;
};

#endif