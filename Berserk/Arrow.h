#ifndef ARROW_HEADER
#define ARROW_HEADER
#include "EnemyBase.h" //Maybe should be instanceBase im unsure
class Bow;
class Arrow : public InstanceBase
{
	using InstanceBase::InstanceBase;

public:
	Arrow();
	~Arrow();
	virtual void Init() override;
	virtual void Update() override;
	virtual void EndDraw(sf::RenderWindow* window) override;



private:
	int mySpeed; 
	int myDamage;
	int myallowedLifeTime;
	int myLifeTimer;
	Bow *myBowOrigin;
};


#endif // !ARROW_HEADER

