#pragma once
#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <array>

#include "Application.h"
#include "TouchEnabledObject.h"
#include "InteractiveGraphicsObject.h"

class WavefunctionAnimation : public InteractiveGraphicsObject
{
public:
	WavefunctionAnimation();
	void setRevolutionTime(int time);
	void draw(uint32_t time) override;
	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	void rebuild();
private:
	int REVOLUTION_TIME = 2000;
	int X = 0, Y = 270, WIDTH = 480, HEIGHT = 40, FRAMES = REVOLUTION_TIME / 80;
	const double PI = std::acos(-1);
	static constexpr float DIVISION = 30.f;
	const int RANGE = HEIGHT / 2;
	const int BASE_Y = Y + HEIGHT / 2;
	int ADDITIONAL_PIXELS = 4 * DIVISION;
	int sinF(double x);
	std::vector<std::vector<SDL_Point>> points;
	SDL_Renderer* renderer;
};

