#include "Text.h"

Text::Text()
{
	renderer = Application::getCurrent()->getRenderer();
}

Text::~Text()
{
	if (textTexture != nullptr)
		SDL_DestroyTexture(textTexture);

	if (textSurface != nullptr)
		SDL_FreeSurface(textSurface);
}

void Text::setText(const char* text)
{
	this->text = text;
	build();
}

void Text::setGeometry(Rect geom)
{
	geometry = geom;
	build();
}

void Text::setColor(Color c)
{
	textColor = c;
	build();
}

void Text::setFontPath(const std::string& fontPath)
{
	this->fontPath = fontPath;
	font.reset(new Font(fontPath, fontSize));
	build();
}

void Text::setFontSize(int fontSize)
{
	this->fontSize = fontSize;
	font.reset(new Font(fontPath, fontSize));
	build();
}

void Text::draw(uint32_t time)
{
	if (textTexture != nullptr)
	{
		SDL_Rect sdlTextPos = geometry;
		SDL_RenderCopy(renderer, textTexture, NULL, &sdlTextPos);
	}
}


int Text::getX() const
{
	return geometry.x;
}

int Text::getY() const
{
	return geometry.y;
}

int Text::getWidth() const
{
	return geometry.width;
}

int Text::getHeight() const
{
	return geometry.height;
}

void Text::build()
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

		if (text.size() > 0)
		{
			textSurface = TTF_RenderText_Solid(*font, text.c_str(), textColor);

			if (!textSurface) {
				throw TTFFontException("Couldn't render text");
			}

			textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

			if (geometry.width == -1 || geometry.height == -1)
			{
				SDL_QueryTexture(textTexture, NULL, NULL, &geometry.width, &geometry.height);
			}
		}
	}
}
