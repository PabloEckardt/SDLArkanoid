#pragma once
#include "Point.h"
#include <iosfwd>

namespace arkanoid
{

class Brick
{
public:
	// Implement the member functions listed below
	Brick(Point p, int32_t w, int32_t h);
	Point leftup;
	int32_t width, height;

	Point getUpperLeft() const;
	Point getLowerRight() const;
};


}
