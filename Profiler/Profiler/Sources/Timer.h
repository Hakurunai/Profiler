#ifndef TIMER__H
#define TIMER__H

#include <iostream>
#include <chrono>
#include <string>


class Timer
{
public :
	Timer(const char* name) : mName(name) 
	{
		mStart = std::chrono::high_resolution_clock::now();
	}

	~Timer();

	__forceinline const std::string Name() const { return std::string(mName); }
	__forceinline const size_t Duration() const { return mDuration; }

protected :
	const char* mName;
	size_t mDuration{ 0 };
	std::chrono::high_resolution_clock::time_point mStart;
};

#endif // TIMER__H