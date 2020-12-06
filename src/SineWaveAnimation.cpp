#include "SineWaveAnimation.h"

SineWaveAnimation::SineWaveAnimation()
	: renderer(Application::getCurrent()->getRenderer())
{
	points.resize(WIDTH + ADDITIONAL_PIXELS);
	for (int i = 0; i < 480 + ADDITIONAL_PIXELS; i++) {
		points[i] = sinF(i);
	}
}

void SineWaveAnimation::draw(uint32_t time)
{
	int offset = int(std::round(((time % REVOLUTION_TIME) / (double)REVOLUTION_TIME) * ADDITIONAL_PIXELS));
	SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);
	SDL_RenderDrawPoints(renderer, makePoints(points, WIDTH, offset), WIDTH);
}

int SineWaveAnimation::getX() const
{
	return X;
}

int SineWaveAnimation::getY() const
{
	return Y;
}

int SineWaveAnimation::getWidth() const
{
	return WIDTH;
}

int SineWaveAnimation::getHeight() const
{
	return HEIGHT;
}

int SineWaveAnimation::sinF(double x)
{
	return int(std::round(std::sin(x / DIVISION * PI) * RANGE + BASE_Y));
}

const SDL_Point* SineWaveAnimation::makePoints(const std::vector<int>& points, int count, int offset)
{
	for (int i = 0; i < count; i++) {
		buffer[i] = { i, points[i + offset] };
	}
	return buffer;
}
