#pragma once
#include <SDL2/SDL.h>
#include <vector>

#include "Application.h"
#include "TouchEnabledObject.h"
#include "InteractiveGraphicsObject.h"

class SineWaveAnimation : public InteractiveGraphicsObject
{
public:
	SineWaveAnimation();
	void draw(uint32_t time) override;
	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
private:
	static constexpr int X = 0, Y = 270, WIDTH = 480, HEIGHT = 40;
	const double PI = std::acos(-1);
	static constexpr float DIVISION = 30.f;
	const int RANGE = HEIGHT / 2;
	const int BASE_Y = Y + HEIGHT / 2;
	static constexpr int REVOLUTION_TIME = 2000;
	int ADDITIONAL_PIXELS = 4 * DIVISION;
	int sinF(double x);
	const SDL_Point* makePoints(const std::vector<int>& points, int count, int offset);
	std::vector<int> points;
	SDL_Renderer* renderer;
	SDL_Point buffer[WIDTH];
};

