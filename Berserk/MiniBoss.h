#ifndef	MINIBOSS_HEADER
#define MINIBOSS_HEADER
#include "EnemyBase.h"
#include "Sword.h"
#include "Bow.h"
class MiniBoss : public EnemyBase
{
	using EnemyBase::EnemyBase;

public:
	//MiniBoss();
	~MiniBoss();
	virtual void Init() override;
	virtual void Update() override;

private:
	enum bossAttackState
	{
		spin, stab, poke, swing, parry, bow, sizeUp, offblanace //NOTE WE NEED T O KEEP OFFBALANCE AS THE LAST ONE TO USE THIS SYSTEM!!!!!!!!
	};
	bossAttackState myAttackState;
	Bow* myBow;
	Sword* mySword;
	float TESTSpin;

	int myDefaultStabTime;
	int mystabTimer;
	int myStabExtensionTime;

	int mySwordSwingDir;
	int mySwordSwingChargeTimer;

	int myDefualtStateChangerTime;
	int myStateChangerTimer;

	int mySwordDist;
	int mySwordDefaultDist;
	int mySwordExtendedDist;
	bool mySwordExtended;
	float mySwordSwingSpd;
	float mySwordSwingExtSpd;
	float mySwordSwingMoveSpd;
	float mySwordExtendSpd;
	bool myExtended;

	int myMoveSpd;
};


#endif // !MINIBOSS_HEADER