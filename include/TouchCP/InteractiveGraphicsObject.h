#pragma once

/**
 * @file InteractiveGraphicsObject.h
 * @author Paolo Infante (info@paoloinfante.it)
 * @brief 
 * @version 1.0.0
 * @date 2020-12-17
 * 
 * Copyright (c) 2020 Paolo Infante
 * 
 */
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
