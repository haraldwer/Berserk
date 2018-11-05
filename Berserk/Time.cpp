#include "pch.h"
#include "Time.h"

float Time::delta = 1;
std::chrono::time_point<std::chrono::high_resolution_clock> Time::previousTime = std::chrono::high_resolution_clock::now();

Time::Time()
{
	previousTime = std::chrono::high_resolution_clock::now();
	delta = 1;
}

void Time::Init()
{
	Time();
}

void Time::NewFrame()
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed = (currentTime - previousTime);
	delta = abs(elapsed.count()) / 16; // Abs cuz time cant be negative duh

	previousTime = currentTime;
	// Somehow a negative value or 0
	if (delta <= 0)
	{
		delta = 1;
	}
}

float Time::DeltaTime()
{
	return delta;
}

Time::~Time()
{
}
