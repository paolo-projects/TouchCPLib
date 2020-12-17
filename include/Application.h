#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <unistd.h>
#include <linux/vt.h>
#include <linux/kd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <memory>
#include <functional>

#include "Window.h"
#include "SceneManager.h"
#include "TouchInput.h"
#include "TouchEventDispatcher.h"
#include "IMGException.h"
#include "TTFFontException.h"
#include "TouchCPException.h"
#include "WorkerThread.h"
#include "MainThreadTaskRunner.h"

/**
 * @brief The main application class. You can only initialize one instance.
 * Typically, you instanciate it in main() and then call run()
*/
class Application
{
public:
	/**
	 * @brief Create an application
	 * @param width The window width
	 * @param height The window height
	 * @param bgColor The background color
	 * @param touchInputDevice The path to the touch device (e.g. /dev/input/event0)
	 * @param ttyDevice The path to the UART device (e.g. /dev/ttyS0)
	 * @param FPS_LIMIT The framerate limit, to avoid stressing the CPU for low Hz displays
	*/
	Application(int width, int height, SDL_Color bgColor, std::string touchInputDevice, std::string ttyDevice, int FPS_LIMIT);
	~Application();

	Application(const Application &copy) = delete;
	Application operator=(const Application &copy) = delete;

	/**
	 * @brief Start the application
	*/
	void run();
	bool isRunning();
	/**
	 * @brief Get the SDL window object
	 * @return The SDL window object
	*/
	SDL_Window *getWindow();
	/**
	 * @brief Get the SDL renderer object
	 * @return The SDL renderer object
	*/
	SDL_Renderer *getRenderer();
	/**
	 * @brief Get the scene manager, needed to change the currently displayed scene
	 * @return The scene manager
	*/
	SceneManager *getSceneManager();
	/**
	 * @brief Runs the given task on the worker thread. It will be deleted when done
	 * @param task The task to run
	*/
	void runOnWorkerThread(Task *task);
	/**
	 * @brief Runs the given task on the main thread. It will be deleted when done
	 * @param task The task to run
	*/
	void runOnMainThread(Task *task);
	/**
	 * @brief Get the SDL window object (static shortcut)
	 * @return The SDL window object
	*/
	static SDL_Window *getCurrentWindow();
	/**
	 * @brief Get the SDL renderer object (static shortcut)
	 * @return The SDL renderer object
	*/
	static SDL_Renderer *getCurrentRenderer();
	/**
	 * @brief Get the scene manager, needed to change the currently displayed scene (static shortcut)
	 * @return The scene manager
	*/
	static SceneManager *getCurrentSceneManager();
	/**
	 * @brief Runs the given task on the worker thread. It will be deleted when done (static shortcut)
	 * @param task The task to run
	*/
	static void runOnCurrentWorkerThread(Task *task);
	/**
	 * @brief Runs the given task on the main thread. It will be deleted when done (static shortcut)
	 * @param task The task to run
	*/
	static void runOnCurrentMainThread(Task *task);
	/**
	 * @brief Exit the application
	*/
	void exit();

	/**
	 * @brief Get the currently running application, or null if none is available
	 * @return The application
	*/
	static Application *getCurrent();

private:
	static Application *application;
	void MainLoop();
	void ProcessEvents(TouchEventDispatcher &touchEventDispatcher, const ts_sample_mt touch_event);
	void DisableTTYCursor();
	void EnableTTYCursor();

	SceneManager sceneManager;
	bool running = true;
	int width, height;
	SDL_Color bgColor;
	std::string touchInputDevice, ttyDevice;
	SDL_Window *window;
	SDL_Renderer *renderer;
	uint32_t lastTouchEvent;
	std::unique_ptr<Window> mainWindow;
	std::unique_ptr<TouchInput> touchInput;
	// This order is important
	MainThreadTaskRunner taskRunner;
	WorkerThread workerThread;
	///

	static constexpr int TOUCH_DEBOUNCE_MS = 250;
	static constexpr int SAMPLES = 5;
	static constexpr int SLOTS = 1;
	int FPS = 30;
	unsigned int FRAMETIME = 1000 / FPS;
};
