#include "pch.h"
#include "Input.h"
#include <Windows.h>

int Input::mouseX;
int Input::mouseY;
int Input::mouseGlobalX;
int Input::mouseGlobalY;

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

int Input::GetMouseGlobalX()
{
	return mouseGlobalX;
}

int Input::GetMouseGlobalY()
{
	return mouseGlobalY;
}

bool Input::MouseDown(int aKey)
{
	switch (aKey)
	{
	case mbRight:
		return sf::Mouse::Right;
		break;
	case mbLeft:
		return sf::Mouse::Left;
		break;
	default:
		return false;
		break;
	}
}

void Input::UpdateInput(sf::RenderWindow * window)
{
	mouseX = sf::Mouse::getPosition(*window).x;
	mouseY = sf::Mouse::getPosition(*window).y;
	mouseGlobalX = window->mapPixelToCoords(sf::Mouse::getPosition(*window)).x;
	mouseGlobalY = window->mapPixelToCoords(sf::Mouse::getPosition(*window)).y;
	
}
