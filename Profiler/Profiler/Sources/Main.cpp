#include "Profiler.h"


void func1()
{
    START_TIMER
    for (int i = 0; i < 100'000; ++i)
    {}
    STOP_TIMER("func1")
}

void func2()
{
    START_TIMER
    for (int i = 0; i < 1'000'000; ++i)
    {
    }
    STOP_TIMER("func2")
}

int main()
{
    func1();
    func2();
}