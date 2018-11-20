#ifndef PLAYER_SWORD_HEADER
#define PLAYER_SWORD_HEADER
#include "InstanceBase.h"
class PlayerSword : public InstanceBase
{
	using InstanceBase::InstanceBase;

public:
	PlayerSword();
	~PlayerSword();
	virtual void Init() override;
	virtual void Update() override;
	
};
#endif
