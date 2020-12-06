#include "ImageButton.h"
ImageButton::ImageButton(int x, int y, int width, int height, SDL_Color fillColor, std::string imageFile) :
	renderer(Application::getCurrent()->getRenderer()), x(x), y(y), width(width), height(height), fillColor(fillColor), imageFile(imageFile)
{
	rectangle = { x, y, width, height };

	imgTexture = IMG_LoadTexture(renderer, imageFile.c_str());

	if (!imgTexture) {
		throw IMGException("Couldn't load image %s", imageFile.c_str());
	}

	int imgHeight, imgWidth;
	SDL_QueryTexture(imgTexture, NULL, NULL, &imgWidth, &imgHeight);

	int marginVert = (height - imgHeight) / 2;
	int marginHor = (width - imgWidth) / 2;
	imgPosition = { x + marginHor, y + marginVert, imgWidth, imgHeight };
}

ImageButton::ImageButton(int x, int y, int width, int height, SDL_Color fillColor, std::string imageFile, int imgWidth, int imgHeight) :
	renderer(Application::getCurrent()->getRenderer()), x(x), y(y), width(width), height(height), fillColor(fillColor), imageFile(imageFile)
{
	rectangle = { x, y, width, height };

	imgTexture = IMG_LoadTexture(renderer, imageFile.c_str());

	if (!imgTexture) {
		throw IMGException("Couldn't load image %s", imageFile.c_str());
	}

	int marginVert = (height - imgHeight) / 2;
	int marginHor = (width - imgWidth) / 2;
	imgPosition = { x + marginHor, y + marginVert, imgWidth, imgHeight };
}

ImageButton::~ImageButton()
{
	SDL_DestroyTexture(imgTexture);
}

void ImageButton::draw(uint32_t time)
{
	SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
	SDL_RenderFillRect(renderer, &rectangle);
	SDL_RenderCopy(renderer, imgTexture, NULL, &imgPosition);
}

int ImageButton::getX() const
{
	return x;
}

int ImageButton::getY() const
{
	return y;
}

int ImageButton::getWidth() const
{
	return width;
}

int ImageButton::getHeight() const
{
	return height;
}
