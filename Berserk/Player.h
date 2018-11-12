#ifndef PLAYER_HEADER
#define PLAYER_HEADER
#include "InstanceBase.h"
class Player : public InstanceBase
{
	using InstanceBase::InstanceBase;

public:
	virtual void Init() override;
	virtual void BeginUpdate() override;
	virtual void Die() override;
	virtual void DealDamage(int damage) override;
	Player();
	~Player();

private:
	// General stuff
	float myAttackTimer;
	int myAttackCD;
	float myMoveAcc;
	float myMoveFric;

	// Animation stuff
	std::string baseSprite;
	int currentAnim;
	float subImg;
	enum AnimStates { idle, running, attacking };
};
#endif
