#pragma once
#include <vector>
#include <algorithm>

#include "InteractiveGraphicsObject.h"
#include "GraphicsScene.h"
#include "SceneManager.h"

/**
 * @brief A class that takes care of dispatching the touch events
 * to the right objects of the displayed scene
*/
class TouchEventDispatcher
{
public:
	TouchEventDispatcher(SceneManager& sceneManager);
	void dispatchTouchEvent(int x, int y);
private:
	SceneManager& sceneManager;
};

