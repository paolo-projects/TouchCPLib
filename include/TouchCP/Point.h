#pragma once

/**
 * @file Point.h
 * @author Paolo Infante (info@paoloinfante.it)
 * @brief 
 * @version 1.0.0
 * @date 2020-12-17
 * 
 * Copyright (c) 2020 Paolo Infante
 * 
 */
#include <SDL2/SDL.h>
#include <stdint.h>

struct Point
{
	int x, y;

	operator SDL_Point() const
	{
		return {
			x, y};
	}
};

template <typename T>
struct PointT
{
	T x, y;
};