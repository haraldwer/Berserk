#include "Control.h"
#include "Game.h"

// Control is the game-controller. 
// This is where all game-related logic on a non-instance level should be executed.

void Control::Init()
{
	// Init logic here
	Game::AddInstance(Game::player, "player", 100, 100, true,false);
}

Control::Control()
{
}

Control::~Control()
{
}
