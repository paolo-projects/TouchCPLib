#include "Text.h"

Text::Text(const char* text, int x, int y, int width, int height, SDL_Color textColor, TTF_Font* font)
	: renderer(Application::getCurrent()->getRenderer()), x(x), y(y), width(width), height(height), textColor(textColor), font(font)
{
	rectangle = { x, y, width, height };

	textSurface = TTF_RenderText_Solid(font, text, textColor);

	if (!textSurface) {
		throw TTFFontException("Couldn't render text");
	}

	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	textPosition = { x, y, width, height };
}

Text::~Text()
{
	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);
}

void Text::setText(const char* text)
{
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;

	textSurface = TTF_RenderText_Solid(font, text, textColor);

	if (!textSurface) {
		throw TTFFontException("Couldn't render text");
	}

	SDL_DestroyTexture(textTexture);
	textTexture = nullptr;

	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	textPosition = { x, y, width, height };
}

void Text::draw(uint32_t time)
{
	SDL_RenderCopy(renderer, textTexture, NULL, &textPosition);
}


int Text::getX() const
{
	return x;
}

int Text::getY() const
{
	return y;
}

int Text::getWidth() const
{
	return width;
}

int Text::getHeight() const
{
	return height;
}