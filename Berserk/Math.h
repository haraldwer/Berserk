#ifndef MATH_HEADER
#define MATH_HEADER
class Math
{
public:
	Math();
	~Math();

	static float PointDistance(float x1, float y1, float x2, float y2);
	static float PointDirection(float x1, float y1, float x2, float y2);
};
#endif