#pragma once
#include <deque>
#include <mutex>
#include <condition_variable>
#include <thread>

#include "Task.h"

/**
 * @brief A class that spawns an Executor Thread (or worker thread).
 * The thread is used for handling intensive and I/O operations without
 * burdening the main thread, which should only care about drawing stuff
*/
class WorkerThread
{
public:
	WorkerThread();
	~WorkerThread();
	/**
	 * @brief Adds a new task to the queue. It will be deleted when done
	 * @param task The task to add
	*/
	void runOnWorker(Task* task);
private:
	void workerThreadRunner();

	std::thread workerThread;
	std::mutex taskDequeMutex;
	std::condition_variable cv;
	std::deque<Task*> taskDeque;
	bool isRunning = true;
};

