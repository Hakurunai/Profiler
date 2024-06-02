#ifndef TIMER__H
#define TIMER__H

#include <iostream>
#include <chrono>
#include <string>

#include "Definitions.h"

struct SProfilerDataNode;

class Timer
{
public :
	Timer(const char* name, SProfilerDataNode& target) : mName(name), mTarget(target)
	{
		mStart = std::chrono::high_resolution_clock::now();
	}

	~Timer();

	FORCEINLINE const std::string Name() const { return std::string(mName); }
	FORCEINLINE const size_t Duration() const { return mDuration; }

	SProfilerDataNode& mTarget;

protected :
	const char* mName;
	size_t mDuration{ 0 };
	std::chrono::high_resolution_clock::time_point mStart;
};

#endif // TIMER__H