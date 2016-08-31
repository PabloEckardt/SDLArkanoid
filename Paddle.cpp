#include "Paddle.h"

#include <ostream>


	Paddle::Paddle(Point p, int32_t w, int32_t h, int32_t v):pt({p.x,p.y}),width(w),height(h),velocity(v)
	{

	}
	Point Paddle::getUpperLeft() const{
		return this -> pt;
	};
	Point Paddle::getLowerRight() const{
		Point lrpt{pt.x + width, pt.y + height};
		return   lrpt;
	};
	int32_t Paddle::getVelocity() const{
		return  this ->velocity;
	};
