#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Application.h"
#include "TTFFontException.h"
#include "InteractiveGraphicsObject.h"

class Button : public InteractiveGraphicsObject
{
public:
	Button() = delete;
	Button(const char* text, int x, int y, int width, int height, SDL_Color fillColor, SDL_Color textColor, TTF_Font* font);
	~Button();
	void draw(uint32_t time) override;
	int getX() const override;
	int getY() const override;
	int getWidth() const override;
	int getHeight() const override;
private:
	SDL_Renderer* renderer;
	int x, y, width, height;
	bool touchEnabled = true, propagateInter = false;
	SDL_Rect rectangle, textPosition;
	SDL_Color fillColor;
	SDL_Color textColor;
	TTF_Font* font;
	SDL_Surface* textSurface;
	SDL_Texture* textTexture;
};

