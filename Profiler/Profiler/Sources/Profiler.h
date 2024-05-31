#ifndef PROFILER__H
#define PROFILER__H

#include <iostream>
#include <chrono>

class Timer
{
public :
	Timer(const char* name) : mName(name) 
	{
		mStart = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - mStart);
		std::cout << mName << " : " << duration.count() << "ms\n";
	}
protected :
	const char* mName;
	std::chrono::high_resolution_clock::time_point mStart;
};

#endif // PROFILER__H