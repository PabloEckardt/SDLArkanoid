#pragma once
#include "Point.h"

class Ball
{
public:
	// members
	static const int32_t DefaultHorizontalVelocity  = 8;
	static  const int32_t DefaultVerticalVelocity  = 8;
	int32_t rad;
	Velocity vel;
	Point pt;
	Ball(Point c, int32_t r, Velocity v);
	//functions
	Velocity getVelocity() const;
	Point getCenter() const;
	int32_t getRadius() const;
};
