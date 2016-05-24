#pragma once

#include "Input.h"
#include "Point.h"

#include <iosfwd>

namespace arkanoid
{

class Paddle
{
public:
	static constexpr int32_t DefaultVelocity = 10;

	// Implement the member functions listed below
	Point pt;
	int32_t width, height, velocity;
	Paddle(Point p, int32_t w, int32_t h, int32_t v);

	Point getUpperLeft() const;
	Point getLowerRight() const;
	int32_t getVelocity() const;
};

// Additional logic to let std::cout work with Paddle objects
std::ostream& operator<<(std::ostream&, const Paddle&);

}
