#ifndef TIMERENTRY__H
#define TIMERENTRY__H

#include "Definitions.h"

struct STimerEntry
{
	size_t count() const { return mCount; }
	size_t time() const { return mTime; }

	FORCEINLINE void AddCount() { ++mCount; }
	FORCEINLINE void AddTiming(const size_t time) { mTime += time; }

	void AddTime(const size_t time)
	{
		++mCount;
		mTime += time;
	}

	std::string GetData() const
	{
		std::string toPrint = "was called ";
		toPrint.append(std::to_string(mCount));
		toPrint.append(" times for ");
		toPrint.append(std::to_string(mTime));
		toPrint.append(" us\n");
		return toPrint;
	}

private:
	size_t mCount{ 0 };
	size_t mTime{ 0 };
};

#endif // TIMERENTRY__H