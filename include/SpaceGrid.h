#pragma once

class SpaceGrid5x3 {
public:
	SpaceGrid5x3(int col, int row) {
		x = H_LAT_PADD + (col) * (WIDTH + H_INT_PADD);
		y = V_LAT_PADD + (row) * (HEIGHT + V_INT_PADD);
	}
	SpaceGrid5x3(int col, int row, int spanH, int spanV) {
		x = H_LAT_PADD + (col) * (WIDTH + H_INT_PADD);
		y = V_LAT_PADD + (row) * (HEIGHT + V_INT_PADD);
		width += (spanH - 1) * (WIDTH + H_INT_PADD);
		height += (spanV - 1) * (HEIGHT + V_INT_PADD);
	}
	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
	int getWidth() const {
		return width;
	}
	int getHeight() const {
		return height;
	}
private:
	static constexpr int H_LAT_PADD = 40, H_INT_PADD = 25, V_LAT_PADD = 40, V_INT_PADD = 30;
	static constexpr int WIDTH = 60, HEIGHT = 60;
	int width = WIDTH, height = HEIGHT;
	int x, y;
};