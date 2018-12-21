#include "Control.h"
#include "Game.h"

// Control is the game-controller. 
// This is where all game-related logic on a non-instance level should be executed.

void Control::Init()
{
	// Init logic here
	Game::AddInstance(Game::player, "player", 100, 100, true,false);
	Game::AddInstance(Game::crate, "crate",300,300, true,true);
	Game::AddInstance(Game::stalker, "basicSword", 1000, 1000, true,false);
}

Control::Control()
{
}

Control::~Control()
{
}
