#include "pch.h"
#include "Math.h"
#include <cmath>

float Math::pi = 3.14159265359f;

Math::Math()
{
}

Math::~Math()
{
}

float Math::PointDistance(float x1, float y1, float x2, float y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

float Math::DirToRad(float dir)
{
	return dir / 180 / pi;
}

float Math::RadToDir(float rad)
{
	return rad * 180 / pi;
}

float Math::PointDirection(float x1, float y1, float x2, float y2)
{
	return atan2(y2 - y1, x2 - x1);
}

float Math::DirDiff(float aDir, float anotherDir)
{
	while (anotherDir > 360)
	{
		anotherDir -= 360;
	}
	while (anotherDir < 0)
	{
		anotherDir += 360;
	}

	while (aDir > 360)
	{
		aDir -= 360;
	}
	while (aDir < 0)
	{
		aDir += 360;
	}

	float returnDir = anotherDir - aDir;

	if (returnDir > 180)
	{
		returnDir = -360 + returnDir;
	}
	if (returnDir < -180)
	{
		returnDir = 360 + returnDir;
	}

	return returnDir;
}