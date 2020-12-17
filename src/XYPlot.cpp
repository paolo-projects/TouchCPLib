#include "TouchCP/XYPlot.h"

XYPlot::XYPlot()
{
	renderer = Application::getCurrent()->getRenderer();
}

XYPlot::~XYPlot()
{
}

void XYPlot::setData(const std::vector<float> &xValues, const std::vector<float> &yValues)
{
	assert(xValues.size() == yValues.size());
	this->xValues = xValues; // Store a reference to avoid copying?
	this->yValues = yValues;

	buildPoints();
}

void XYPlot::setXMinMax(const Optional<std::pair<float, float>> &xMinMax)
{
	this->xMinMax = xMinMax;
	buildPoints();
}

void XYPlot::setYXMinMax(const Optional<std::pair<float, float>> &yMinMax)
{
	this->yMinMax = yMinMax;
	buildPoints();
}

void XYPlot::setGeometry(Rect r)
{
	geometry = r;
	buildPoints();
}

void XYPlot::setBackgroundColor(const Color bgColor)
{
	backgroundColor = bgColor;
}

void XYPlot::setLineColor(const Color lnColor)
{
	lineColor = lnColor;
}

void XYPlot::draw(uint32_t time)
{
	// Draw rectangle fill
	if (backgroundColor.a != 0)
	{
		SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
		SDL_Rect sdlGeom = geometry;
		SDL_RenderFillRect(renderer, &sdlGeom);
	}
	// Draw rectangle perimeter
	SDL_SetRenderDrawColor(renderer, lineColor.r, lineColor.g, lineColor.b, lineColor.a * 0.5);
	SDL_Point perimeter[5] = {
		{geometry.x, geometry.y},
		{geometry.x + geometry.width, geometry.y},
		{geometry.x + geometry.width, geometry.y + geometry.height},
		{geometry.x, geometry.y + geometry.height},
		{geometry.x, geometry.y}};
	SDL_RenderDrawLines(renderer, perimeter, 5);
	// Draw data points
	SDL_SetRenderDrawColor(renderer, lineColor.r, lineColor.g, lineColor.b, lineColor.a);
	SDL_RenderDrawPoints(renderer, renderedPoints.data(), renderedPoints.size());
}

int XYPlot::getX() const
{
	return geometry.x;
}

int XYPlot::getY() const
{
	return geometry.y;
}

int XYPlot::getWidth() const
{
	return geometry.width;
}

int XYPlot::getHeight() const
{
	return geometry.height;
}

void XYPlot::buildPoints()
{
	if (xValues.size() > 0 && yValues.size() == xValues.size())
	{
		renderedPoints.clear();
		renderedPoints.reserve(2 * geometry.width);

		std::pair<float, float> min_max_x;
		std::pair<float, float> min_max_y;

		if (xMinMax.hasValue())
		{
			min_max_x = xMinMax.get();
		}
		else
		{
			auto min_max_x_it = std::minmax_element(xValues.begin(), xValues.end());
			min_max_x = {*min_max_x_it.first, *min_max_x_it.second};
		}

		if (yMinMax.hasValue())
		{
			min_max_y = yMinMax.get();
		}
		else
		{
			auto min_max_y_it = std::minmax_element(yValues.begin(), yValues.end());
			min_max_y = {*min_max_y_it.first, *min_max_y_it.second};
		}

		float xScaler = geometry.width / (min_max_x.second - min_max_x.first);
		float yScaler = geometry.height / (min_max_y.second - min_max_y.first);

		const auto findInDataset = [this](int x, int y) {
			for (const auto &val : renderedPoints)
			{
				if (x == val.x && y == val.y)
					return true;
			}
			return false;
		};

		const int yTop = geometry.y + geometry.height;

		for (size_t i = 0; i < xValues.size(); i++)
		{
			int xPnt = std::round((xValues[i] - min_max_x.first) * xScaler + min_max_x.first + geometry.x);
			int yPnt = std::round((((min_max_y.second - yValues[i]) - min_max_y.first) * yScaler + min_max_y.first) + geometry.y);

			if (!findInDataset(xPnt, yPnt))
			{
				renderedPoints.emplace_back(SDL_Point{xPnt, yPnt});
			}
		}
	}
}
