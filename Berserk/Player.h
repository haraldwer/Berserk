#ifndef PLAYER_HEADER
#define PLAYER_HEADER
#include "InstanceBase.h"
#include "Game.h"
class Player : public InstanceBase
{
	using InstanceBase::InstanceBase;

	public:
		~Player();
		virtual void Init() override;
		virtual void Update() override;
		virtual void EndUpdate() override;
		virtual void Die() override;
		virtual void DealDamage(int damage) override; 

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
		InstanceBase* mySword;
		float mySwordSwingSpd;
		float mySwordSwingMoveSpd;
		float mySwordExtendSpd;

		// Animation stuff
		std::string baseSprite;
		int currentAnim;
		float subImg;
		enum AnimStates { idle, running, attacking };
};
#endif
