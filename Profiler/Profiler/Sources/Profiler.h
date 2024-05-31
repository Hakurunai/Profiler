#ifndef PROFILER__H
#define PROFILER__H

#include <iostream>
#include <chrono>

#define START_TIMER auto start = std::chrono::high_resolution_clock::now();

// do while loop -> create a scope when expanded, so all variables in it are locale
// there is something about semicolon too, it appears that a do-while loop can protect
//from syntax error (forget to add a semicolon after invocation of the macro)
#define STOP_TIMER(name) \
	do\
	{\
		auto end = std::chrono::high_resolution_clock::now();\
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);\
		std::cout << name << " : " << duration.count() << "ms\n";\
	}\
	while(false);

#endif // PROFILER__H