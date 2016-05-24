#include "Brick.h"

#include <ostream>

namespace arkanoid
{

	Brick::Brick(Point p, int32_t w, int32_t h):leftup{p.x,p.y }, width(w),height(h){};
	Point Brick::getUpperLeft() const{
	return leftup;
	};
Point Brick::getLowerRight() const{
	Point lr({leftup.x + width, height + leftup.y});
	return lr;
};

std::ostream& operator<<(std::ostream& os, const Brick& brick) {
	os << "Brick { " << brick.getUpperLeft() << ", " << brick.getLowerRight() << " }";
	return os;
}

}
