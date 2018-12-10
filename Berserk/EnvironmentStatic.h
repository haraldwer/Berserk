#ifndef ENVIRONMENTSTATIC_HEADER
#define ENVIRONMENTSTATIC_HEADER
#include "InstanceBase.h"
class EnvironmentStatic :
	public InstanceBase
{
	using InstanceBase::InstanceBase;

public:
	EnvironmentStatic();
	~EnvironmentStatic();
	virtual void Init() override;
};
#endif