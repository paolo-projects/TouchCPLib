#include "SceneManager.h"

SceneManager::SceneManager()
{
}

void SceneManager::setCurrentScene(std::string sceneName)
{
	if (registeredScenes.find(sceneName) != registeredScenes.end()) {
		currentScene = registeredScenes[sceneName];
	}
}

GraphicsScene* SceneManager::getCurrentScene()
{
	return currentScene;
}

void SceneManager::registerScene(const std::string& sceneName, GraphicsScene* scene)
{
	if (registeredScenes.find(sceneName) != registeredScenes.end()) {
		registeredScenes.erase(sceneName);
	}
	registeredScenes.insert(std::make_pair(sceneName, scene));
}

void SceneManager::unregisterScene(const std::string& sceneName)
{
	if (registeredScenes.find(sceneName) != registeredScenes.end()) {
		registeredScenes.erase(sceneName);
	}
}

void SceneManager::unregisterScene(GraphicsScene* scene)
{
	for (auto it = registeredScenes.begin(); it != registeredScenes.end(); it++) {
		if (it->second == scene) {
			registeredScenes.erase(it);
			break;
		}
	}
}

SceneManager::~SceneManager()
{
}
