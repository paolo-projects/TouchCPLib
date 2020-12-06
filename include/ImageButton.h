#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Application.h"
#include "InteractiveGraphicsObject.h"
#include "IMGException.h"

class ImageButton :
	public InteractiveGraphicsObject
{
public:
	ImageButton() = delete;
	ImageButton(int x, int y, int width, int height, SDL_Color fillColor, std::string imageFile);
	ImageButton(int x, int y, int width, int height, SDL_Color fillColor, std::string imageFile, int imgWidth, int imgHeight);
	~ImageButton();
	void draw(uint32_t time) override;
	int getX() const override;
	int getY() const override;
	int getWidth() const override;
	int getHeight() const override;
private:
	SDL_Renderer* renderer;
	int x, y, width, height;
	bool touchEnabled = true, propagateInter = false;
	SDL_Rect rectangle, imgPosition;
	SDL_Color fillColor;
	SDL_Texture* imgTexture;
	std::string imageFile;
};

