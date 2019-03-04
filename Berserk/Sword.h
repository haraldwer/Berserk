#ifndef SWORD_HEADER
#define SWORD_HEADER
#include "EnemyBase.h"
class Sword : public InstanceBase
{
	using InstanceBase::InstanceBase;

private: 

public:
	~Sword();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw(sf::RenderWindow* window, bool editorOpen) override; //varför överskriver inte denna???
	virtual void EndDraw(sf::RenderWindow* window) override;
	float myDamage;
	float mySwingThresh;
	bool myDropped;
	bool mySwappedShow;
};
#endif
