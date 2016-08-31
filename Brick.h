#pragma once
#include "Point.h"

class Brick
{
public:
	// Implement the member functions listed below
	Brick(Point p, int32_t w, int32_t h);
	Point leftup;
	int32_t width, height;
	short live = 1;

	Point getUpperLeft() const;
	Point getLowerRight() const;
	void displayPoint();
};
