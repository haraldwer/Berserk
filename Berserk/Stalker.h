#ifndef STALKER_HEADER
#define STALKER_HEADER
#include "EnemyBase.h"
#include "Sword.h"

class Stalker : public EnemyBase
{
	using EnemyBase::EnemyBase;
	
	private:
		float myMoveSpd = 1;

		enum swordAttackState
		{
			spin, stab, poke, swing, parry, offblanace
		};
		swordAttackState myAttackState;
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
		Sword* mySword;
		float mySwordSwingSpd;
		float mySwordSwingExtSpd;
		float mySwordSwingMoveSpd;
		float mySwordExtendSpd;
		bool myExtended;



	public:
		Stalker();
		~Stalker();
		void Update() override;
		void Init() override;
};

#endif