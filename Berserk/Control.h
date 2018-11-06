#ifndef CONTROL_HEADER
#define CONTROL_HEADER
#include "InstanceBase.h"
class Control : public InstanceBase
{
	using InstanceBase::InstanceBase;

public:
	virtual void Init() override;

private:
	Control();
	~Control();
};
#endif

