#ifndef TIME_HEADER
#define TIME_HEADER
#include <chrono>
class Time
{
private:
	static float delta;
	static std::chrono::time_point<std::chrono::steady_clock> previousTime;

public:
	Time();
	~Time();
	static void Init();
	static void NewFrame();
	static float DeltaTime();
};
#endif