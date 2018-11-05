#include "pch.h"
#include "Math.h"
#include <cmath>

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

float Math::PointDirection(float x1, float y1, float x2, float y2)
{
	return atan2(y2 - y1, x2 - x1);
}