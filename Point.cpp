#include "Point.h"

#include <ostream>



Point updatePoint(Point p, Velocity v) {
	return { p.x + v.vx, p.y + v.vy };
}
