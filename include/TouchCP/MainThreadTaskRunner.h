#pragma once

/**
 * @file MainThreadTaskRunner.h
 * @author Paolo Infante (info@paoloinfante.it)
 * @brief 
 * @version 1.0.0
 * @date 2020-12-17
 * 
 * Copyright (c) 2020 Paolo Infante
 * 
 */
#include <mutex>
#include <deque>
#include "Task.h"

class MainThreadTaskRunner
{
public:
	MainThreadTaskRunner();
	~MainThreadTaskRunner();
	/**
	 * @brief Adds a new task to the queue. It will be deleted when done
	 * @param task The task to add
	*/
	void addTask(Task *task);
	/**
	 * @brief Run the pending tasks
	*/
	void runTasks();

private:
	std::mutex taskDequeMutex;
	std::deque<Task *> taskDeque;
};
