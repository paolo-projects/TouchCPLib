#pragma once
#include <SDL2/SDL.h>
#include <algorithm>
#include <functional>
#include "Color.h"

class XiaolinWu
{
public:
	// integer part of x
	static int ipart(float x)
	{
		return (int)x;
	}
	static int round(float x)
	{
		return ipart(x + 0.5);
	}
	// fractional part of x
	static float fpart(float x) {
		return x - (int)(x);
	}
	static int rfpart(int x)
	{
		return 1.f - fpart(x);
	}
	static void drawLine(float x0, float y0, float x1, float y1, std::function<void(int, int, float)> plot)
	{
		bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);

		if (steep)
		{
			std::swap(x0, y0);
			std::swap(x1, y1);
		}
		if (x0 > x1)
		{
			std::swap(x0, x1);
			std::swap(y0, y1);
		}

		float dx = x1 - x0;
		float dy = y1 - y0;
		float gradient = dy / dx;
		if (dx == 0.0)
		{
			gradient = 1.0;
		}

		// handle first endpoint
		float xend = round(x0);
		float yend = y0 + gradient * (xend - x0);
		float xgap = rfpart(x0 + 0.5);
		float xpxl1 = xend; // this will be used in the main loop
		float ypxl1 = ipart(yend);
		if (steep)
		{
			plot(ypxl1, xpxl1, rfpart(yend) * xgap);
			plot(ypxl1 + 1, xpxl1, fpart(yend) * xgap);
		}
		else
		{
			plot(xpxl1, ypxl1, rfpart(yend) * xgap);
			plot(xpxl1, ypxl1 + 1, fpart(yend) * xgap);
		}
		float intery = yend + gradient; // first y-intersection for the main loop

	// handle second endpoint
		xend = round(x1);
		yend = y1 + gradient * (xend - x1);
		xgap = fpart(x1 + 0.5);
		float xpxl2 = xend; //this will be used in the main loop
		float ypxl2 = ipart(yend);
		if (steep)
		{
			plot(ypxl2, xpxl2, rfpart(yend) * xgap);
			plot(ypxl2 + 1, xpxl2, fpart(yend) * xgap);
		}
		else
		{
			plot(xpxl2, ypxl2, rfpart(yend) * xgap);
			plot(xpxl2, ypxl2 + 1, fpart(yend) * xgap);
		}

		// main loop
		if (steep)
		{
			for (int x = xpxl1 + 1; x < xpxl2; x++)
			{
				plot(ipart(intery), x, rfpart(intery));
				plot(ipart(intery) + 1, x, fpart(intery));
				intery = intery + gradient;
			}
		}
		else
		{
			for (int x = xpxl1 + 1; x < xpxl2; x++)
			{
				plot(x, ipart(intery), rfpart(intery));
				plot(x, ipart(intery) + 1, fpart(intery));
				intery = intery + gradient;
			}
		}
	}
};

