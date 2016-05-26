#pragma once

#include "Paddle.h"

#include <iosfwd>

namespace arkanoid
{

class Ball
{
public:
	static constexpr int32_t DefaultHorizontalVelocity = 8;
	static constexpr int32_t DefaultVerticalVelocity = 8;

	// Implement the member functions listed below
	int32_t rad;
	Velocity vel;
	Point pt;
	Ball(Point c, int32_t r, Velocity v);

	Velocity getVelocity() const;
	Point getCenter() const;
	int32_t getRadius() const;
};

// Additional logic to let std::cout work with Ball objects
std::ostream& operator<<(std::ostream&, const Ball&);

}
