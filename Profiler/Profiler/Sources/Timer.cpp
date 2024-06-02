#include "Timer.h"
#include "Profiler.h"
#include "ProfilerDataNode.h"

Timer::~Timer()
{
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - mStart);
	mDuration = duration.count();

	mTarget.mTimerData.AddTime(mDuration);
	Profiler::Instance().TimerEndDelegate();
}