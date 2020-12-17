#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Application.h"
#include "InteractiveGraphicsObject.h"
#include "IMGException.h"
#include "Rect.h"
#include "Color.h"

/**
 * @brief A simple image button
*/
class ImageButton :
	public InteractiveGraphicsObject
{
public:
	ImageButton();
	~ImageButton();
	/**
	 * @brief Set the button geometry (position and size)
	 * @param geom The button geometry
	*/
	void setGeometry(Rect geom);
	/**
	 * @brief Set the fill color
	 * @param color Fill color
	*/
	void setFillColor(Color color);
	/**
	 * @brief Set the image file
	 * @param imgFile The path to the image
	*/
	void setImageFile(const std::string& imgFile);
	/**
	 * @brief Set the image size. The image is automatically centered
	 * @param width The image width
	 * @param height The image height
	*/
	void setImageSize(int width, int height);
	void draw(uint32_t time) override;
	int getX() const override;
	int getY() const override;
	int getWidth() const override;
	int getHeight() const override;
private:
	void build();
	SDL_Renderer* renderer = nullptr;
	Rect geometry = { 0, 0, 0, 0 }, imgPosition;
	Color fillColor = { 0, 0, 0, 0xFF };
	SDL_Texture* imgTexture = nullptr;
	std::string imageFile;
	int imgW = -1, imgH = -1;
};

