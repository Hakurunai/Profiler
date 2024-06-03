#ifndef TIMERENTRY__H
#define TIMERENTRY__H

#include "Definitions.h"
#include <string>

struct STimerEntry
{
	FORCEINLINE size_t Count() const { return mCount; }
	FORCEINLINE size_t Time() const { return mTime; }

	FORCEINLINE void AddCount() { ++mCount; }
	FORCEINLINE void AddTime(const size_t time) { mTime += time; }

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
	size_t mCount{ 1 };
	size_t mTime{ 0 };
};

#endif // TIMERENTRY__H