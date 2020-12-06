#include "Button.h"

Button::Button(const char* text, int x, int y, int width, int height, SDL_Color fillColor, SDL_Color textColor, TTF_Font* font) :
	renderer(Application::getCurrent()->getRenderer()), x(x), y(y), width(width), height(height), fillColor(fillColor), textColor(textColor)
{
	rectangle = { x, y, width, height };

	textSurface = TTF_RenderText_Solid(font, text, textColor);

	if (!textSurface) {
		throw TTFFontException("Couldn't render text");
	}

	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	int textW = textSurface->w;
	int textH = textSurface->h;

	int marginVert = (height - textH) / 2;
	int marginHor = (width - textW) / 2;
	textPosition = { x + marginHor, y + marginVert, textW, textH };
}

Button::~Button()
{
	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);
}

void Button::draw(uint32_t time)
{
	SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
	SDL_RenderFillRect(renderer, &rectangle);
	SDL_RenderCopy(renderer, textTexture, &textSurface->clip_rect, &textPosition);
}

int Button::getX() const
{
	return x;
}

int Button::getY() const
{
	return y;
}

int Button::getWidth() const
{
	return width;
}

int Button::getHeight() const
{
	return height;
}
