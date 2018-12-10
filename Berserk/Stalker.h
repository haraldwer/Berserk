#ifndef STALKER_HEADER
#define STALKER_HEADER
#include "EnemyBase.h"

class Stalker : public EnemyBase
{
	using EnemyBase::EnemyBase;
	
	private:
		float myMoveSpd = 1;

	public:
		Stalker();
		~Stalker();
		void Update() override;
		void Init() override;
};

#endif