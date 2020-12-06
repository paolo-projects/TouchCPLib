#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Application.h"
#include "InteractiveGraphicsObject.h"

class Text :
	public InteractiveGraphicsObject
{
public:
	Text(const char* text, int x, int y, int width, int height, SDL_Color textColor, TTF_Font* font);
	~Text();
	void setText(const char* text);
	void draw(uint32_t time) override;
	int getX() const override;
	int getY() const override;
	int getWidth() const override;
	int getHeight() const override;
private:
	SDL_Renderer* renderer;
	int x, y, width, height;
	SDL_Color textColor;
	TTF_Font* font;
	SDL_Rect rectangle, textPosition;
	SDL_Surface* textSurface;
	SDL_Texture* textTexture;
};

