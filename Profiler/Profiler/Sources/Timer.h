#ifndef TIMER__H
#define TIMER__H

#include <chrono>

struct SProfilerDataNode;

class Timer
{
public :
	Timer(SProfilerDataNode& target) : mTarget(target)
	{
		mStart = std::chrono::high_resolution_clock::now();
	}
	Timer() = delete;
	~Timer();

	SProfilerDataNode& mTarget;

protected :
	std::chrono::high_resolution_clock::time_point mStart;
};

#endif // TIMER__H