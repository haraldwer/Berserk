#ifndef DOOR_HEADER
#define DOOR_HEADER
#include "InstanceBase.h"

class Door : public InstanceBase
{
	using InstanceBase::InstanceBase;

public:
	Door();
	~Door();
	virtual void Init() override;
	virtual void Update() override;
	bool myOpened;
};

#endif