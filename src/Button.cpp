#include "Button.h"

Button::Button()
{
	renderer = Application::getCurrent()->getRenderer();
}

Button::~Button()
{
	if (textTexture != nullptr)
		SDL_DestroyTexture(textTexture);

	if (textSurface != nullptr)
		SDL_FreeSurface(textSurface);
}

void Button::setText(const std::string& text)
{
	this->text = text;
	build();
}

void Button::setGeometry(Rect r)
{
	geometry = r;
	build();
}

void Button::setFillColor(const Color fillColor)
{
	this->fillColor = fillColor;
}

void Button::setTextColor(const Color textColor)
{
	this->textColor = textColor;
	build();
}

void Button::setFontPath(const std::string& fontPath)
{
	this->fontPath = fontPath;
	font.reset(new Font(fontPath, fontSize));
	build();
}

void Button::setFontSize(int fontSize)
{
	this->fontSize = fontSize;
	font.reset(new Font(fontPath, fontSize));
	build();
}

void Button::draw(uint32_t time)
{
	SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
	SDL_Rect sdlGeom = geometry;
	SDL_RenderFillRect(renderer, &sdlGeom);
	if (textTexture != nullptr)
	{
		SDL_RenderCopy(renderer, textTexture, NULL, &textPosition);
	}
}

int Button::getX() const
{
	return geometry.x;
}

int Button::getY() const
{
	return geometry.y;
}

int Button::getWidth() const
{
	return geometry.width;
}

int Button::getHeight() const
{
	return geometry.height;
}

void Button::build()
{
	if (font != nullptr) {
		if (textSurface != nullptr)
		{
			SDL_FreeSurface(textSurface);
			textSurface = nullptr;
		}
		if (textTexture != nullptr)
		{
			SDL_DestroyTexture(textTexture);
			textTexture = nullptr;
		}

		textSurface = TTF_RenderText_Solid(*font, text.c_str(), textColor);

		if (!textSurface) {
			throw TTFFontException("Couldn't render text");
		}

		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		int textW = textSurface->w;
		int textH = textSurface->h;

		int marginVert = (geometry.height - textH) / 2;
		int marginHor = (geometry.width - textW) / 2;
		textPosition = { geometry.x + marginHor, geometry.y + marginVert, textW, textH };
	}
}
