#ifndef PLAYER_HEADER
#define PLAYER_HEADER
#include "EnemyBase.h"
#include "Sword.h"
#include "Game.h"
class Player : public EnemyBase
{
	using EnemyBase::EnemyBase;

	public:
		//Player();
		~Player();
		virtual void Init() override;
		virtual void Update() override;
		virtual void EndUpdate() override;
		virtual void Die();
		virtual void DealDamage(int damage); 

	private:
		// General stuff
		float myAttackTimer;
		int myAttackCD;
		float myMoveAcc;
		float myMoveFric;
		float mySwordDist;
		float myViewSpd;
		
		int mySwordDefaultDist;
		int mySwordExtendedDist;
		bool mySwordExtended;
		Sword* mySword;
		float mySwordSwingSpd;
		float mySwordSwingExtSpd;
		float mySwordSwingMoveSpd;
		float mySwordExtendSpd;

		// Animation stuff
		std::string baseSprite;
		int currentAnim;
		float subImg;
		enum AnimStates { idle, running, attacking };
};
#endif
