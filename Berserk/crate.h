#ifndef CRATE_HEADER
#define CRATE_HEADER
#include "InstanceBase.h"
class Crate : public InstanceBase
{
	using InstanceBase::InstanceBase;

public:
	~Crate();
	virtual void Init() override;

private:

};

#endif // !CRATE_HEADER
