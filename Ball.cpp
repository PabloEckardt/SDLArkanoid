#include "Ball.h"



	Ball::Ball(Point c, int32_t r, Velocity v):rad{r},vel{ v.vx, v.vy },	pt({ c.x, c.y }) {}
	
	Velocity Ball::getVelocity() const{
		return this-> vel;
	};
	Point Ball::getCenter() const{
		return this->pt;
	};
	int32_t Ball::getRadius() const{
		return this->rad;
	};
