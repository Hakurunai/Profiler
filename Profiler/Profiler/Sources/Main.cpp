#include "Profiler.h"

void func1()
{
    Timer t("func1");
    for (int i = 0; i < 100'000; ++i)
    {}
}

void func2()
{
    Timer t("func2");
    for (int i = 0; i < 1'000'000; ++i)
    {
    }
}

int main()
{
    func1();
    func2();
}