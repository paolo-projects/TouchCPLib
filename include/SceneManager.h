#pragma once
#include <map>

#include "GraphicsScene.h"

/**
 * @brief The scene manager controls which scene is currently displayed, in addition to
 * enumerating the scenes currently loaded into memory. It can be accessed from the global
 * application instance
*/
class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	/**
	 * @brief Change the currently displayed scene. It has to be registered through `registerScene` before you can display it.
	 * @param sceneName The name of the scene.
	*/
	void setCurrentScene(std::string sceneName);
	GraphicsScene* getCurrentScene();
	/**
	 * @brief Register a scene for displaying it later. It will NOT take ownership of the scene, so it's your job to free its memory later, if needed.
	 * @param sceneName The scene identifier
	 * @param scene The scene object
	*/
	void registerScene(const std::string& sceneName, GraphicsScene* scene);
	/**
	 * @brief Unregister a scene
	 * @param scene The scene object
	*/
	void unregisterScene(GraphicsScene* scene);
	/**
	 * @brief Unregister a scene
	 * @param sceneName The scene name
	*/
	void unregisterScene(const std::string& sceneName);
private:
	GraphicsScene* currentScene;
	std::map<std::string, GraphicsScene*> registeredScenes;
};

