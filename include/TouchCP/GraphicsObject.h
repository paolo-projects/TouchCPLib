#pragma once
/**
 * @file GraphicsObject.h
 * @author Paolo Infante (info@paoloinfante.it)
 * @brief The GraphicsObject base class
 * @version 1.0.0
 * @date 2020-12-17
 * 
 * Copyright (c) 2020 Paolo Infante
 * 
 */
#include <stdint.h>

/**
 * @brief A simple interface for all the graphic objects that are supposed to be drawn
*/
class GraphicsObject
{
public:
	virtual ~GraphicsObject() = default;
	/**
	 * @brief The draw method. It will be called once per frame for each object in a scene
	 * @param time A time parameter (as given by SDL_GetTicks) for time-based animation purposes
	*/
	virtual void draw(uint32_t time) = 0;
	bool isVisible() const
	{
		return visibility;
	}
	void setVisibility(bool visible)
	{
		visibility = visible;
	}

private:
	bool visibility = true;
};