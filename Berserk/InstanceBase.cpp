#include "pch.h"
#include "InstanceBase.h"
#include <SFML\Graphics.hpp>

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
	sf::Sprite tempSprite = SpriteLib::GetSprite(mySpriteName);
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
	sf::Sprite sprite = SpriteLib::GetSprite(mySpriteName);
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
