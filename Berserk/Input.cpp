#include "pch.h"
#include "Input.h"
#include <Windows.h>

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
