#pragma once
#include <SDL2/SDL.h>
#include <stdint.h>

struct Color {
	uint8_t r, g, b, a;

	operator SDL_Color() const
	{
		return SDL_Color{
			r, g, b, a
		};
	}
};