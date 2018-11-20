#include "pch.h"
#include "Input.h"
#include <Windows.h>

int Input::mouseX;
int Input::mouseY;

Input::Input()
{
}

Input::~Input()
{
}

bool Input::KeyDown(char aKey)
{
	// To prevent game from pausing
	if (GetKeyState(aKey) < 0)
	{
		return true;
	}
	return false;
}

int Input::GetMouseX()
{
	return mouseX;
}

int Input::GetMouseY()
{
	return mouseY;
}

void Input::UpdateInput(sf::RenderWindow * window)
{
	mouseX = sf::Mouse::getPosition(*window).x;
	mouseY = sf::Mouse::getPosition(*window).y;
}
