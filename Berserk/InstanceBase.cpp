#include "pch.h"
#include "InstanceBase.h"

InstanceBase::InstanceBase()
{
	// Default and empty
}

InstanceBase::InstanceBase(int aType, const std::string &aSpriteName, const float &anX, const float &aY)
	:
	mySpriteName(aSpriteName),
	myX(anX),
	myY(aY),
	myHSpd(0),
	myVSpd(0),
	myAlpha(1),
	myDir(0),
	myDestroy(false),
	myHScale(1),
	myVScale(1),
	myType(aType),
	myHP(0)
{
	Sprite tempSprite = SpriteLib::GetSprite(mySpriteName);
	myWCentering = tempSprite.width / 2;
	myHCentering = tempSprite.height / 2;
}

void InstanceBase::Init()
{
}

void InstanceBase::BeginUpdate()
{
}

void InstanceBase::Update()
{
}

void InstanceBase::EndUpdate()
{
	myX += myHSpd * Time::DeltaTime();
	myY += myVSpd * Time::DeltaTime(); // Delta
}

void InstanceBase::BeginDraw()
{
}

void InstanceBase::Draw()
{
	// Draw sprite
}

void InstanceBase::EndDraw()
{
}

void InstanceBase::DealDamage(int damage)
{
	myHP -= damage;
	if (myHP < 0)
	{
		Die();
	}
}

void InstanceBase::Die()
{
	myDestroy = true;
}

InstanceBase::~InstanceBase()
{
	// Remove all variables from memory
}
