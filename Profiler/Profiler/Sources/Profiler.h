#ifndef PROFILER__H
#define PROFILER__H

#include "Timer.h"
#include <map>
#include <string>

class Profiler
{
private:
	struct TimerEntry
	{
		size_t count() const { return mCount; }
		size_t time() const { return mTime; }

		void AddTime(const size_t time)
		{
			++mCount;
			mTime += time;
		}

	private:
		size_t mCount{ 0 };
		size_t mTime{ 0 };
	};

public:

	Profiler(const Profiler& other) = delete;
	Profiler& operator=(const Profiler& other) = delete;

	static Profiler& Instance()
	{
		static Profiler instance;
		return instance;
	}

	Timer StartTimer(const char* name) { return Timer(name); }
	
	void AddTimerData(const Timer& timer) { mTimersMap[timer.Name()].AddTime(timer.Duration()); };

	/// <summary>
	/// Use to determnine 
	/// </summary>
	void StopFrame() 
	{
		++mFrameNumber;
		PrintData();
		//TODO : check that clear keep the previous allocated memory -> some functions will be called each frame
		mTimersMap.clear(); 
	}

private :

	size_t mFrameNumber; //assuming 120 fps : max(size_t) / (120 fps * 60 s/min * 60 min/h * 24 h/day * 365 day/year) = 4.8 * 10^9 years to be a max value and wrap around self
	std::map<std::string, TimerEntry> mTimersMap;
	Profiler() = default;
	~Profiler() = default;

	void PrintData()
	{
		std::cout << "Frame number " << mFrameNumber << " :\n";
		for (const auto& data : mTimersMap)
		{
			std::cout << data.first << " was called " << data.second.count()
				<< " times for " << data.second.time() << " us in total\n";
		}
		std::cout << std::endl;
	}
};


#endif // PROFILER__H