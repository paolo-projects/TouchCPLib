#pragma once

/**
 * @file Task.h
 * @author Paolo Infante (info@paoloinfante.it)
 * @brief 
 * @version 1.0.0
 * @date 2020-12-17
 * 
 * Copyright (c) 2020 Paolo Infante
 * 
 */
#include <functional>

/**
 * @brief A task is an object that wraps the code to run on an thread
*/
class Task
{
public:
	Task(std::function<void(void)> runner) : runner(runner){};
	// Unneeded overhead since the std::function alone is enough, but we keep it like this for now
	void operator()()
	{
		runner();
	}

private:
	std::function<void(void)> runner;
};
