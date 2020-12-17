#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Application.h"
#include "InteractiveGraphicsObject.h"
#include "Rect.h"
#include "Color.h"
#include "Font.h"

/**
 * @brief A simple text object
*/
class Text :
	public InteractiveGraphicsObject
{
public:
	Text();
	~Text();
	/**
	 * @brief Set the text message
	 * @param text The text to display
	*/
	void setText(const char* text);
	/**
	 * @brief Set the text geometry (position and size). If width and height are set to -1 the text natural size will be used
	 * @param geom The text geometry
	*/
	void setGeometry(Rect geom);
	/**
	 * @brief Set the text color
	 * @param c The text color
	*/
	void setColor(Color c);
	/**
	 * @brief Set the text font
	 * @param fontPath The path to the font
	*/
	void setFontPath(const std::string& fontPath);
	/**
	 * @brief Set the font size
	 * @param fontSize The font size
	*/
	void setFontSize(int fontSize);
	void draw(uint32_t time) override;
	int getX() const override;
	int getY() const override;
	int getWidth() const override;
	int getHeight() const override;
private:
	void build();
	std::string text;
	SDL_Renderer* renderer;
	Rect geometry;
	Color textColor;
	std::unique_ptr<Font> font;
	Rect textPosition;
	SDL_Surface* textSurface = nullptr;
	SDL_Texture* textTexture = nullptr;
	std::string fontPath;
	int fontSize = 12;
};

