#include "MainScene.h"
#include "ImageButton.h"
#include "SineWaveAnimation.h"
#include "SamplingScene.h"

MainScene::MainScene()
{
	// The scene manager can be retrieved from the global application instance
	// You can get it through the ::getCurrent() static method on the Application class
	SceneManager* sceneManager = Application::getCurrentSceneManager();
	int width, height;

	SDL_Window* window = Application::getCurrent()->getWindow();
	SDL_GetWindowSize(window, &width, &height);

	SpaceGrid5x3 startBtnPos(0, 0);
	SpaceGrid5x3 exitBtnPos(4, 0);

	// Objects have to be instanciated through the new keyword.
	// The scene will take care of freeing up their memory after it is destroyed
	// This only works for objects that are added to the scene
	// If you have dangling objects around your scene you have to take care of their disposal by yourself
	exitBtn = new ImageButton();
	exitBtn->setGeometry({ exitBtnPos.getX(), exitBtnPos.getY(), exitBtnPos.getWidth(), exitBtnPos.getHeight() });
	exitBtn->setFillColor({ 0xEE, 0xEE, 0xEE, 0xFF });
	exitBtn->setImageSize(28, 28);
	exitBtn->setImageFile("logout.png");

	auto exitBtnCallback = []() {
		Application::getCurrent()->exit();
	};

	exitBtn->setTouchCallback(exitBtnCallback);
	// You can add objects to a scene by using the base class addObject() method
	addObject(exitBtn);

	startBtn = new ImageButton();
	startBtn->setGeometry({ startBtnPos.getX(), startBtnPos.getY(), startBtnPos.getWidth(),startBtnPos.getHeight() });
	startBtn->setFillColor({ 0x99, 0x99, 0x0, 0xFF });
	startBtn->setImageSize(28, 28);
	startBtn->setImageFile("settings-white.png");

	auto startBtnPress = [sceneManager]() {
		sceneManager->setCurrentScene("SamplingScene");
	};

	startBtn->setTouchCallback(startBtnPress);
	addObject(startBtn);

	sineAnim = new SineWaveAnimation();
	addObject(sineAnim);

	samplingScene = new SamplingScene();
	sceneManager->registerScene("SamplingScene", samplingScene);
}

MainScene::~MainScene() {
	Application::getCurrentSceneManager()->unregisterScene(samplingScene);
	delete samplingScene;
}