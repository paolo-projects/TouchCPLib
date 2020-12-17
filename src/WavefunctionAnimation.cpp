#include "WavefunctionAnimation.h"

WavefunctionAnimation::WavefunctionAnimation()
	: renderer(Application::getCurrent()->getRenderer())
{
	rebuild();
}

void WavefunctionAnimation::setRevolutionTime(int time)
{
	REVOLUTION_TIME = time;
	FRAMES = REVOLUTION_TIME / 80;
}

void WavefunctionAnimation::draw(uint32_t time)
{
	int frame = (int)std::round((time % (2 * REVOLUTION_TIME)) / (double)(2 * REVOLUTION_TIME) * (FRAMES * 2 - 1));
	if (frame > FRAMES - 1) {
		frame = (FRAMES * 2 - 1) - frame;
	}
	auto& data = points[frame];
	SDL_SetRenderDrawColor(renderer, 0xEB, 0xB1, 0x34, 0xFF);
	SDL_RenderDrawPoints(renderer, data.data(), WIDTH);
}

int WavefunctionAnimation::getX() const
{
	return X;
}

int WavefunctionAnimation::getY() const
{
	return Y;
}

int WavefunctionAnimation::getWidth() const
{
	return WIDTH;
}

int WavefunctionAnimation::getHeight() const
{
	return HEIGHT;
}

void WavefunctionAnimation::rebuild()
{
	points.clear();
	points.resize(FRAMES);
	for (int i = 0; i < FRAMES; i++) {
		points[i].resize(WIDTH);
		const double scale = 1 - 2 / (double)FRAMES * i;
		for (int n = 0; n < WIDTH; n++) {
			points[i][n] = { n, (int)std::round((sinF(n) - BASE_Y) * scale + BASE_Y) };
		}
	}
}

int WavefunctionAnimation::sinF(double x)
{
	return int(std::round(std::sin(x / WIDTH * 2 * PI) * RANGE + BASE_Y));
}
