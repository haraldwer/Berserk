#ifndef BOWMAN_HEADER
#define BOWMAN_HEADER
#include "EnemyBase.h"
#include "Bow.h"

class BowMan : public EnemyBase
{
	using EnemyBase::EnemyBase;
	
private:
	Bow* myBow;
	int myShootingTimer;
	int myShootingMaxTime;

	float myMoveSpd = 1;

public:
	BowMan();
	~BowMan();
	void Update() override;
	void Init() override;
};

#endif // !BOWMAN_HEADER
