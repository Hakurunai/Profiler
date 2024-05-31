#include "Timer.h"
#include "Profiler.h"

Timer::~Timer()
{
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - mStart);
	mDuration = duration.count();
	Profiler::Instance().AddTimerData(*this);
}
