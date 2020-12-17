#pragma once
#include <functional>

/**
 * @brief A task is an object that wraps the code to run on an thread
*/
class Task
{
public:
	Task(std::function<void(void)> runner) : runner(runner) {};
	// Unneeded overhead since the std::function alone is enough, but we keep it like this for now
	void operator()()
	{
		runner();
	}
private:
	std::function<void(void)> runner;
};

