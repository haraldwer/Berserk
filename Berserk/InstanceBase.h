#ifndef INSTANCE_BASE_HEADER
#define INSTANCE_BASE_HEADER
#include <string>
#include "SpriteLib.h"
#include <Windows.h>
#include "Time.h"

class InstanceBase
{
private:

public:
	virtual void Init();
	virtual void BeginUpdate();
	virtual void Update();
	virtual void EndUpdate();

	virtual void BeginDraw();
	virtual void Draw();
	virtual void EndDraw();

	virtual void DealDamage(int damage);
	virtual void Die();

	InstanceBase();
	explicit InstanceBase(int aType, const std::string &aSpriteName, const float &anX, const float &aY);
	virtual ~InstanceBase();

	float
		myX,
		myY,
		myHSpd,
		myVSpd,
		myAlpha,
		myDir;

	bool
		myDestroy;

	int
		myWCentering,
		myHCentering,
		myHScale,
		myVScale,
		myRoom,
		myType,
		myHP;

	std::string mySpriteName;
};

#endif