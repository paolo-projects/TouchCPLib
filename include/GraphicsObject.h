#pragma once
#include <stdint.h>

/**
 * @brief A simple interface for all the graphic objects that are supposed to be drawn
*/
class GraphicsObject
{
public:
	/**
	 * @brief The draw method. It will be called once per frame for each object in a scene
	 * @param time A time parameter (as given by SDL_GetTicks) for time-based animation purposes
	*/
	virtual ~GraphicsObject() = default;
	virtual void draw(uint32_t time) = 0;
};