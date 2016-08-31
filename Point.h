#pragma once

#include <cstdint>
#include <iosfwd>



struct Point
{
	int32_t x, y;
};

struct Velocity
{
	int32_t vx, vy;
};


Point updatePoint(Point, Velocity);
