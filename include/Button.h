#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Application.h"
#include "TTFFontException.h"
#include "InteractiveGraphicsObject.h"
#include "Color.h"
#include "Font.h"
#include "Rect.h"

/**
 * @brief A simple text button
*/
class Button : public InteractiveGraphicsObject
{
public:
	Button();
	~Button();
	/**
	 * @brief Sets the button text
	 * @param text The button text
	*/
	void setText(const std::string& text);
	/**
	 * @brief Sets the button geometry (position and size)
	 * @param r The button geometry
	*/
	void setGeometry(Rect r);
	/**
	 * @brief Set the fill color
	 * @param fillColor The fill color
	*/
	void setFillColor(const Color fillColor);
	/**
	 * @brief Sete the text color
	 * @param textColor The text color
	*/
	void setTextColor(const Color textColor);
	/**
	 * @brief Set the button text font
	 * @param fontPath The path to the font
	*/
	void setFontPath(const std::string& fontPath);
	/**
	 * @brief Set the button font size
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
	SDL_Renderer* renderer = nullptr;
	std::string text;
	Rect geometry = { 0, 0, 0, 0 };
	SDL_Rect rectangle, textPosition;
	Color fillColor = { 0, 0, 0, 0xFF };
	Color textColor = { 0, 0, 0, 0xFF };
	std::string fontPath;
	int fontSize = 12;
	SDL_Surface* textSurface = nullptr;
	SDL_Texture* textTexture = nullptr;
	std::unique_ptr<Font> font = nullptr;
};

