#ifndef MATH_HEADER
#define MATH_HEADER
class Math
{
public:
	Math();
	~Math();

	static float pi;
	static float PointDistance(float x1, float y1, float x2, float y2);
	static float DirToRad(float dir);
	static float RadToDir(float rad);
	static float PointDirection(float x1, float y1, float x2, float y2);
	static float DirDiff(float aDir, float anotherDir);
};
#endif