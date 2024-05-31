#include "Profiler.h"

void func1()
{
    auto t = Profiler::Instance().StartTimer("func1");
    for (int i = 0; i < 100'000; ++i) {}
}

void func2()
{
    auto t = Profiler::Instance().StartTimer("func2");
    for (int i = 0; i < 1'000'000; ++i) {}    
}

int main()
{
    func1();
    func2();
    func1();
    func2();
    func2();
}