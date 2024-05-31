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

private :

	std::map<std::string, TimerEntry> mTimersMap;
	Profiler() = default;
	~Profiler() 
	{
		for(const auto & data : mTimersMap)
		{
			std::cout << data.first << " was called " << data.second.count() 
						<< " times for " << data.second.time() << " us in total\n";
		}
	};
};


#endif // PROFILER__H