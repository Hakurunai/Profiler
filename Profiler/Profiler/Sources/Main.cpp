#include "Profiler.h"

void func1()
{
    PROFILER_START_TIMER();
    for (int i = 0; i < 10'000; ++i) {}
}


void func2()
{
    PROFILER_START_TIMER();
    for (int i = 0; i < 1'000'000; ++i) {}
    func1();
}

void func3()
{
    PROFILER_START_TIMER();
    for (int i = 0; i < 1'000'000; ++i) {}
    func2();
}

int main()
{
    int i = 0;
    while (i < 2)
    {
        {
            PROFILER_START_TIMER();
            for (int i = 0; i < 1'000'000; ++i) {}

            func1();
            func2();
            func1();
            func2();
            func2();
            func3();
            ++i;
        }
        PROFILER_END_FRAME()
    }
}