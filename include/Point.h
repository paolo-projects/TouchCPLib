#pragma once
#include <SDL2/SDL.h>
#include <stdint.h>

struct Point {
	int x, y;

	operator SDL_Point() const
	{
		return {
			x, y
		};
	}
};

template<typename T>
struct PointT {
	T x, y;
};