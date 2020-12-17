#include "WorkerThread.h"

WorkerThread::WorkerThread()
{
	workerThread = std::thread(&WorkerThread::workerThreadRunner, this);
}

WorkerThread::~WorkerThread()
{
	// Destructor should run from main thread
	// We signal a new task even if we don't add any
	// so the thread will wake up and stop the loop
	std::unique_lock<std::mutex> lock(taskDequeMutex);
	isRunning = false;
	taskDeque.clear();
	cv.notify_one();
	lock.unlock();

	workerThread.join();
}

void WorkerThread::workerThreadRunner()
{
	while (isRunning)
	{
		// Wait until the main thread notifies new task
		std::unique_lock<std::mutex> lock(taskDequeMutex);
		cv.wait(lock);

		// Run the pending tasks
		while (taskDeque.size() > 0)
		{
			Task* task = taskDeque.back();
			(*task)();
			delete task;
			taskDeque.pop_back();
		}

		lock.unlock();
	}
}

void WorkerThread::runOnWorker(Task* task)
{
	std::lock_guard<std::mutex> lock(taskDequeMutex);
	taskDeque.push_front(task);
	cv.notify_one();
}
