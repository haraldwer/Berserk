#ifndef PINETREE_HEADER
#define PINETREE_HEADER
#include "InstanceBase.h"
class PineTree :
	public InstanceBase
{
	using InstanceBase::InstanceBase;

public:
	PineTree();
	~PineTree();
	virtual void Init() override;
};
#endif
