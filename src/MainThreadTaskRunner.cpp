#include "MainThreadTaskRunner.h"

MainThreadTaskRunner::MainThreadTaskRunner()
{
}

MainThreadTaskRunner::~MainThreadTaskRunner()
{
	// Delete the pending tasks
	// The worker thread has to be dead at this point
	// to avoid referencing to a deleted object
	while (taskDeque.size() > 0)
	{
		Task* task = taskDeque.back();
		delete task;
		taskDeque.pop_back();
	}
}

void MainThreadTaskRunner::addTask(Task* task)
{
	std::lock_guard<std::mutex> lock(taskDequeMutex);
	taskDeque.push_front(task);
}

void MainThreadTaskRunner::runTasks()
{
	std::lock_guard<std::mutex> lock(taskDequeMutex);

	// Run the pending tasks
	while (taskDeque.size() > 0)
	{
		Task* task = taskDeque.back();
		(*task)();
		delete task;
		taskDeque.pop_back();
	}
}
