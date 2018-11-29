#ifndef CRATE_HEADER
#define CRATE_HEADER
#include "EnemyBase.h"
class Crate : public EnemyBase
{
	using EnemyBase::EnemyBase;

public:
	~Crate();
	virtual void Init() override;

private:

};

#endif // !CRATE_HEADER
