#pragma once

/**
 * @file Color.h
 * @author Paolo Infante (info@paoloinfante.it)
 * @brief A color wrapper
 * @version 1.0.0
 * @date 2020-12-17
 * 
 * Copyright (c) 2020 Paolo Infante
 * 
 */
#include <SDL2/SDL.h>
#include <stdint.h>

struct Color
{
	uint8_t r, g, b, a;

	operator SDL_Color() const
	{
		return SDL_Color{
			r, g, b, a};
	}
};