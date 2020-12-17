#include "ImageButton.h"
ImageButton::ImageButton()
{
	renderer = Application::getCurrent()->getRenderer();
}

ImageButton::~ImageButton()
{
	if (imgTexture != nullptr)
		SDL_DestroyTexture(imgTexture);
}

void ImageButton::setGeometry(Rect geom)
{
	geometry = geom;
	build();
}

void ImageButton::setFillColor(Color color)
{
	fillColor = color;
}

void ImageButton::setImageFile(const std::string& imgFile)
{
	imageFile = imgFile;
	build();
}

void ImageButton::setImageSize(int width, int height)
{
	imgW = width;
	imgH = height;
	build();
}

void ImageButton::draw(uint32_t time)
{
	SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
	SDL_Rect sdlGeom = geometry;
	SDL_RenderFillRect(renderer, &sdlGeom);
	SDL_Rect sdlImgPos = imgPosition;
	SDL_RenderCopy(renderer, imgTexture, NULL, &sdlImgPos);
}

int ImageButton::getX() const
{
	return geometry.x;
}

int ImageButton::getY() const
{
	return geometry.y;
}

int ImageButton::getWidth() const
{
	return geometry.width;
}

int ImageButton::getHeight() const
{
	return geometry.height;
}

void ImageButton::build()
{
	if (imageFile.length() > 0)
	{
		if (imgTexture != nullptr)
		{
			SDL_DestroyTexture(imgTexture);
			imgTexture = nullptr;
		}

		imgTexture = IMG_LoadTexture(renderer, imageFile.c_str());

		if (!imgTexture) {
			throw IMGException("Couldn't load image %s", imageFile.c_str());
		}

		if (imgW == -1 || imgH == -1)
		{
			SDL_QueryTexture(imgTexture, NULL, NULL, &imgW, &imgH);
		}

		int marginVert = (geometry.height - imgH) / 2;
		int marginHor = (geometry.width - imgW) / 2;
		imgPosition = { geometry.x + marginHor, geometry.y + marginVert, imgW, imgH };
	}
}
