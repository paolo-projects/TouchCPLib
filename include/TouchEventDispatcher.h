#pragma once
#include <vector>
#include <algorithm>

#include "InteractiveGraphicsObject.h"
#include "GraphicsScene.h"
#include "SceneManager.h"

class TouchEventDispatcher
{
public:
	TouchEventDispatcher(SceneManager& sceneManager);
	void dispatchTouchEvent(int x, int y);
private:
	SceneManager& sceneManager;
};

