#ifndef PLAYER_HEADER
#define PLAYER_HEADER
#include "EnemyBase.h"
#include "Sword.h"
#include "Bow.h"
#include "Game.h"
class Player : public EnemyBase
{
	using EnemyBase::EnemyBase;

	public:
		Player();
		~Player();
		virtual void Init() override;
		virtual void Update() override;
		virtual void EndUpdate() override;
		virtual void Die();
		virtual void DealDamage(int damage); 
		Sword* mySword; //VÄLDIGT FULLT ATT FLYTTA UT TILL PUBLIC MEN VI HAR VALLT ATT UNDVIKA ACCESSMETODER
		Sword* mySavedSword;

	private:
		// General stuff
		float myAttackTimer;
		int myAttackCD;
		float myMoveAcc;
		float myMoveFric;
		float mySwordDist;
		float myViewSpd;
		
		int mySwordDefaultDist;
		int mySwordExtendedDist;
		bool mySwordExtended;
		float mySwordSwingSpd;
		float mySwordSwingExtSpd;
		float mySwordSwingMoveSpd;
		float mySwordExtendSpd;
		Bow* myBow;
		Bow* mySavedBow; //ugly but functional selution thats a little cheeky
		bool aiming;
		bool mySwordSelectedBool;
		bool myWeaponSwappedBool;
		bool myEHeld;

		// Animation stuff
		std::string baseSprite;
		int currentAnim;
		float subImg;
		enum AnimStates { idle, running, attacking };
};
#endif
