#include "Brick.h"
#include <iostream>



	Brick::Brick(Point p, int32_t w, int32_t h):leftup{p.x,p.y }, width(w),height(h){};

	Point Brick::getUpperLeft() const{
		return leftup;
	};
	Point Brick::getLowerRight() const{
		Point lr({leftup.x + width, height + leftup.y});
		return lr;
	};
	void Brick::displayPoint (){
		std::cout<< "(" << leftup.x << " " <<  leftup.y << ")"<< std::endl;
	}
