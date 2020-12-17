#pragma once

/**
 * @file XYPlot.h
 * @author Paolo Infante (info@paoloinfante.it)
 * @brief 
 * @version 1.0.0
 * @date 2020-12-17
 * 
 * Copyright (c) 2020 Paolo Infante
 * 
 */
#include <vector>
#include <cassert>
#include "Application.h"
#include "InteractiveGraphicsObject.h"
#include "Point.h"
#include "Rect.h"
#include "Color.h"
#include "Optional.h"

/**
 * @brief A chart displaying X,Y points, scaled to the object geomtry
*/
class XYPlot : public InteractiveGraphicsObject
{
public:
	XYPlot();
	~XYPlot();
	/**
	 * @brief Set the data points
	 * @param xValues The X points
	 * @param yValues The Y points
	*/
	void setData(const std::vector<float>& xValues, const std::vector<float>& yValues);
	/**
	 * @brief Set the X axis minimum and maximum. If unset, it will use the minimum and maximum from the dataset
	 * @param xMinMax An optional pair of minimum, maximum values
	*/
	void setXMinMax(const Optional<std::pair<float, float>>& xMinMax);
	/**
	 * @brief Set the Y axis minimum and maximum. If unset, it will use the minimum and maximum from the dataset
	 * @param yMinMax An optional pair of minimum, maximum values
	*/
	void setYXMinMax(const Optional<std::pair<float, float>>& yMinMax);
	/**
	 * @brief Set the chart geometry (position and size)
	 * @param r The chart geometry
	*/
	void setGeometry(Rect r);
	/**
	 * @brief Set the background color
	 * @param bgColor The background color
	*/
	void setBackgroundColor(const Color bgColor);
	/**
	 * @brief Set the points color (it will also be used for the chart outline)
	 * @param lnColor The points color
	*/
	void setLineColor(const Color lnColor);
	void draw(uint32_t time) override;
	int getX() const override;
	int getY() const override;
	int getWidth() const override;
	int getHeight() const override;
private:
	void buildPoints();
	SDL_Renderer* renderer = nullptr;
	std::vector<float> xValues, yValues;
	std::vector<SDL_Point> renderedPoints;
	Rect geometry = { 0, 0, 0, 0 };
	Color backgroundColor, lineColor;
	Optional<std::pair<float, float>> xMinMax = {};
	Optional<std::pair<float, float>> yMinMax = {};
};

