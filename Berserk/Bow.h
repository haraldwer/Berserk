#ifndef BOW_HEADER
#define BOW_HEADER
#include "EnemyBase.h"
class Bow : public InstanceBase
{
	using InstanceBase::InstanceBase;

private:
	bool dropped;

public:
	~Bow();
	virtual void Init() override;
	virtual void Update() override;
	virtual void EndDraw(sf::RenderWindow* window) override;
	float myDamage;
	int myAmmo; //maybe should be saved somewhere else, in a quil or maybe in the player/enemy that holds it, dont matter dawg 
};


#endif // !BOW_HEADER

