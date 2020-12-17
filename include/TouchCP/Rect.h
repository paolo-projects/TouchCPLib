#pragma once

/**
 * @file Rect.h
 * @author Paolo Infante (info@paoloinfante.it)
 * @brief 
 * @version 1.0.0
 * @date 2020-12-17
 * 
 * Copyright (c) 2020 Paolo Infante
 * 
 */
#include <SDL2/SDL.h>
#include <algorithm>
#include "Point.h"

struct Rect
{
	int x, y, width, height;

	static Rect fromCoords(Point p1, Point p2)
	{
		int xMin = std::min(p1.x, p2.x);
		int yMin = std::min(p1.y, p2.y);

		return {
			xMin,
			yMin,
			std::abs(p1.x - p2.x),
			std::abs(p1.y - p2.y)};
	}

	operator SDL_Rect() const
	{
		return SDL_Rect{
			x, y, width, height};
	}
};