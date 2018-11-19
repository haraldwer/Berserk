#ifndef CRATE_HEADER
#define CRATE_HEADER
#include "InstanceBase.h"
class Crate : public InstanceBase
{
	using InstanceBase::InstanceBase;

public:
	Crate();
	~Crate();
	virtual void Init() override;
	virtual void BeginUpdate() override;
	virtual void Die() override;
	virtual void DealDamage(int damage) override;

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

#endif // !CRATE_HEADER
