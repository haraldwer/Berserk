#ifndef PLAYER_HEADER
#define PLAYER_HEADER
#include "InstanceBase.h"
class Player : public InstanceBase
{
	using InstanceBase::InstanceBase;

	public:
		Player();
		~Player();
		virtual void Init() override;
		virtual void Update() override;
		virtual void Die() override;
		virtual void DealDamage(int damage) override;

	private:
		// General stuff
		float myAttackTimer;
		int myAttackCD;
		float myMoveAcc;
		float myMoveFric;
		InstanceBase* mySword;

		// Animation stuff
		std::string baseSprite;
		int currentAnim;
		float subImg;
		enum AnimStates { idle, running, attacking };
};
#endif
