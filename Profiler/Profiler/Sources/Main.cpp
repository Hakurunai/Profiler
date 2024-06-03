#include "Profiler.h"

void func1()
{
    auto t = Profiler::Instance().StartTimer("func1");
    for (int i = 0; i < 1'000; ++i) {}
}


void func2()
{
    auto t = Profiler::Instance().StartTimer("func2");
    for (int i = 0; i < 1'000'000; ++i) {}
    func1();
}

void func3()
{
    auto t = Profiler::Instance().StartTimer("func3");
    for (int i = 0; i < 1'000'000; ++i) {}
    func2();
}

int main()
{
    int i = 0;
    while (i < 2)
    {
        {
            auto t = Profiler::Instance().StartTimer("main");
            for (int i = 0; i < 1'000'000; ++i) {}

            func1();
            func2();
            func1();
            func2();
            func2();
            func3();
            ++i;
        }
        Profiler::Instance().StopFrame();
    }
}