#ifndef BUTTON_HEADER
#define BUTTON_HEADER
#include "InstanceBase.h"
#include <string>

class Button : public InstanceBase
{
	using InstanceBase::InstanceBase;

public:
	Button();
	~Button();
	virtual void Init() override;
	virtual void Update() override;
	bool pressed;
	bool Permanent;
	std::string myPressedSpriteName;
	std::string myNotPressedSpriteNameSave;
};


#endif // !BUTTON_HEADER




