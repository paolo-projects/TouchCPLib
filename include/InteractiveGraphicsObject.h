#pragma once
#include "GraphicsObject.h"
#include "TouchEnabledObject.h"

/**
 * @brief An abstract class implementing both the GraphicsObject and the
 * TouchEnabledObject, which gives an interactive graphic object as result
*/
class InteractiveGraphicsObject : public GraphicsObject, public TouchEnabledObject
{
public:
	virtual ~InteractiveGraphicsObject() = default;
};

