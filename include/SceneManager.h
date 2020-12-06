#pragma once
#include <map>

#include "GraphicsScene.h"

/**
 * @brief The scene manager controls which scene is currently displayed, in addition to
 * enumerating the scenes currently loaded into memory. It's a global object that can be
 * accessed both through its static methods
*/
class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void setCurrentScene(std::string sceneName);
	GraphicsScene* getCurrentScene();
	void registerScene(const std::string& sceneName, GraphicsScene* scene);
	void unregisterScene(GraphicsScene* scene);
	void unregisterScene(const std::string& sceneName);
private:
	GraphicsScene* currentScene;
	std::map<std::string, GraphicsScene*> registeredScenes;
};

