#ifndef WALL_HEADER
#define WALL_HEADER
#include "EnemyBase.h"
#include "InstanceBase.h"
class Wall : public EnemyBase
{
	using EnemyBase::EnemyBase;

public:
	virtual void Init() override;
	Wall();
	~Wall();

private:

};

#endif