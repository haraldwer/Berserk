#ifndef CRATE_HEADER
#define CRATE_HEADER
#include "EnemyBase.h"
class Crate : public EnemyBase
{
	using EnemyBase::EnemyBase;

public:
	virtual void Init() override;
	~Crate();

private:

};

#endif // !CRATE_HEADER
