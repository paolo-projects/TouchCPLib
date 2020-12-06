#include "Application.h"

Application* Application::application = nullptr;

Application::Application(GraphicsScene* mainScene, int width, int height, SDL_Color bgColor, std::string touchInputDevice, std::string ttyDevice)
	: mainScene(mainScene), width(width), height(height), bgColor(bgColor), touchInputDevice(touchInputDevice), ttyDevice(ttyDevice)
{
	if (application != nullptr) {
		throw std::runtime_error("Can't create multiple instances of application");
	}
	application = this;
	lastTouchEvent = SDL_GetTicks();
}

Application::~Application()
{
	application = nullptr;
}

void Application::ProcessEvents(TouchEventDispatcher& touchEventDispatcher, const ts_sample_mt touch_event)
{
	uint32_t nowTicks = SDL_GetTicks();
	if (touch_event.valid && nowTicks > lastTouchEvent + TOUCH_DEBOUNCE_MS) {
		touchEventDispatcher.dispatchTouchEvent(touch_event.x, touch_event.y);
		lastTouchEvent = SDL_GetTicks();
	}
}

void Application::DisableTTYCursor()
{
	// Switch tty0 to graphics mode
	int tty = open(ttyDevice.c_str(), O_RDWR, 0);
	int res = ioctl(tty, VT_UNLOCKSWITCH, 0);

	if (res == -1) {
		perror("VT_UNLOCKSWITCH to 0 failed, ignoring");
	}

	res = ioctl(tty, KDSETMODE, KD_GRAPHICS);

	if (res == -1) {
		perror("KDSETMODE to KD_GRAPHICS failed, ignoring");
	}

	close(tty);
}

void Application::EnableTTYCursor()
{
	// Switch tty0 to text mode
	int tty = open(ttyDevice.c_str(), O_RDWR, 0);
	int res = ioctl(tty, VT_UNLOCKSWITCH, 1);

	if (res == -1) {
		perror("VT_UNLOCKSWITCH to 1 failed, ignoring");
	}

	res = ioctl(tty, KDSETMODE, KD_TEXT);

	if (res == -1) {
		perror("KDSETMODE to KD_TEXT failed, ignoring");
	}

	close(tty);
}

void Application::setMainScene(GraphicsScene* scene)
{
	mainScene = scene;
}

int Application::run()
{
	int presult = 0;
	try {
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			fprintf(stderr, "Failed while initializing SDL. %s\n", SDL_GetError());
			::exit(1);
		}
		try {
			if (TTF_Init() < 0) {
				SDL_Quit();
				fprintf(stderr, "Failed while initializing TTL. %s\n", TTF_GetError());
				::exit(1);
			}

			try {
				if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0) {
					TTF_Quit();
					SDL_Quit();
					fprintf(stderr, "Failed while initializing SDL IMG Library. %s\n", TTF_GetError());
					::exit(1);
				}

				DisableTTYCursor();
				SDL_ShowCursor(SDL_DISABLE);

				auto onTermination = [](int signal) {
					application->exit();
				};

				signal(SIGINT, onTermination);
				signal(SIGTERM, onTermination);
				signal(SIGKILL, onTermination);

				try {
					MainLoop();
				}
				catch (const std::exception& exc) {
					perror(exc.what());
				}

				signal(SIGINT, SIG_DFL);
				signal(SIGTERM, SIG_DFL);
				signal(SIGKILL, SIG_DFL);

				EnableTTYCursor();

				TTF_Quit();
			}
			catch (const IMGException& exc) {
				perror(exc.what());
				presult = 1;
			}
		}
		catch (const TTFFontException& exc) {
			perror(exc.what());
			presult = 1;
		}
		SDL_Quit();
	}
	catch (const SDLException& exc) {
		perror(exc.what());
		presult = 1;
	}

	return presult;
}

void Application::MainLoop()
{
	TouchEventDispatcher touchEventDispatcher(sceneManager);

	Window mainWindow(width, height, bgColor);
	TouchInput touchInput(touchInputDevice,
		std::bind(&Application::ProcessEvents, this,
			std::ref(touchEventDispatcher), std::placeholders::_1),
		SAMPLES, SLOTS);
	window = mainWindow.getWindowObject();
	renderer = mainWindow.getRenderer();

	sceneManager.registerScene("MainScene", mainScene);

	sceneManager.setCurrentScene("MainScene");

	// Timing
	uint32_t previousTicks = SDL_GetTicks();
	uint32_t currentTicks;

	while (running) {
		// Timing 
		currentTicks = SDL_GetTicks();
		// Touch input
		touchInput.poll();

		if (currentTicks - previousTicks < FRAMETIME) // Avoid stressing the CPU since the SPI screen has a very poor refresh rate
			continue;

		GraphicsScene* currentScene = sceneManager.getCurrentScene();

		if (currentScene != nullptr) {
			currentScene->draw(currentTicks);
		}

		// Timing and render
		previousTicks = currentTicks;
		SDL_RenderPresent(renderer);
		mainWindow.update();
	}
}

bool Application::isRunning()
{
	return application->running;
}

SDL_Window* Application::getWindow()
{
	return application->window;
}

SDL_Renderer* Application::getRenderer()
{
	return application->renderer;
}

SceneManager& Application::getSceneManager()
{
	return sceneManager;
}

void Application::exit()
{
	application->running = false;
}

Application* Application::getCurrent()
{
	return application;
}