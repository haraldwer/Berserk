#ifndef INSTANCE_BASE_HEADER
#define INSTANCE_BASE_HEADER
#include <string>
#include "SpriteLib.h"
#include <Windows.h>
#include "Time.h"
#include <SFML\Graphics.hpp>

class InstanceBase
{
private:

public:
	virtual void Init();
	virtual void BeginUpdate();
	virtual void Update();
	virtual void EndUpdate();

	virtual void BeginDraw(sf::RenderWindow* window);
	virtual void Draw(sf::RenderWindow* window, bool editorOpen);
	virtual void EndDraw(sf::RenderWindow* window);
	
	InstanceBase();
	explicit InstanceBase(int aType, const std::string &aSpriteName, const float &anX, const float &aY, int aRoom, bool doInit, bool saveable);
	virtual ~InstanceBase();

	float
		myX,
		myY,
		myHSpd,
		myVSpd,
		myAlpha,
		myDir;

	bool
		myDestroy,
		myIsSolid,
		myIsPersistent,
		myIsEnemy,
		mySaveFlag;

	int
		myWCentering,
		myHCentering,
		myHScale,
		myVScale,
		myRoom,
		myType,
		myDepth;

	InstanceBase* myID;
	
	sf::RectangleShape myCollider;
	std::string mySpriteName;
};

#endif