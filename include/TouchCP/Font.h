#pragma once
/**
 * @file Font.h
 * @author Paolo Infante (info@paoloinfante.it)
 * @brief A font wrapper
 * @version 1.0.0
 * @date 2020-12-17
 * 
 * Copyright (c) 2020 Paolo Infante
 * 
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Font
{
public:
	Font(const std::string &fontPath, int fontSize) : fontPath(fontPath), fontSize(fontSize)
	{
		font = TTF_OpenFont(fontPath.c_str(), fontSize);
	}
	~Font()
	{
		TTF_CloseFont(font);
	}
	operator TTF_Font *()
	{
		return font;
	}

private:
	std::string fontPath;
	int fontSize;
	TTF_Font *font;
};