#include "World.h"
#include <math.h>
#include <ostream>
#include <iostream>

// Ball WorldBall;
// std::vector<Brick> WorldBricks;
// int32_t w, h;
// Paddle WorldPadle;
//pabloeckardt 3am!
using std::endl;
namespace arkanoid{

	double distance(Point p1, Point p2){
		double  xsq = (p1.x - p2.x )* (p1.x - p2.x );
		double  ysq = (p1.y - p2.y )* (p1.y - p2.y );
		double result =  sqrt(xsq+ysq);
		return result;
}
// bool circlecoll();
//squaredcoll detects a collision between any two squares.
bool squaredcoll(Point rec1, int32_t width1, int32_t height1, Point rec2, int32_t width2, int32_t height2){
				// std::cout<< "rec1.x " << rec1.x << " is <= " << rec2.x + width2 << endl;
				// std::cout<< "rec2.x " << rec2.x << " is <= " << rec1.x + width1 << endl;
				// std::cout<< "rec1.y " << rec1.y << " is <= " << rec2.y + height2 << endl;
				// std::cout<< "rec2.y " << rec2.y << " is <= " << rec1.y + height1 << endl;
				// 	std::cout<<"~~~~~~~~~~~~~~~~~~~\n";

		if (rec1.x <= rec2.x + width2 &&
				rec2.x <= rec1.x + width1  &&
				rec1.y <= rec2.y + height2 &&
				rec2.y <= rec1.y + height1){
					// std::cout<<"~~~~~Collission detected~~~~~\n";
					return true;
				};
					// true as in  collission detected.
		return false;
}
//general function that runs the tests between the shapes.
bool World::thingsCollide(std::vector<Brick> bVect, Paddle pad, Ball ball) const{
			// std::cout<<"vector size is: " << bVect.size() << std::endl;
		for (unsigned j =0; j < bVect.size()-1; j++) {
			Point topleft = bVect[j].getUpperLeft();
			int32_t height = bVect[j].height;
			int32_t width = bVect[j].width;
			for (unsigned k =j+1; k < bVect.size(); k++) {
				// std::cout<<"comparison number : " << k << std::endl;
				Point topleft2 = bVect[k].getUpperLeft();
				int32_t height2 = bVect[k].height;
				int32_t width2 = bVect[k].width;

				if (squaredcoll(topleft,width,height,topleft2, width2,height2)){
					return true;
				}
			}

			// here we are done checking brick vs brick.Then we test the padle with the same function.
			if (squaredcoll(topleft,width,height,topleft2, width2,height2)){
				return true;
			}
		}
		for (unsigned j =0; j < bVect.size(); j++) {
			Point topleft = bVect[j].getUpperLeft();
			int32_t height = bVect[j].height;
			int32_t width = bVect[j].width;
		 if(squaredcoll(topleft,width,height,pad.getUpperLeft(), pad.width, pad.height)){
			//  cout<< "paddle is colliding with something" << endl;
			 return true;
	   }
		}

			//bricks don't collide means false
			return false;
};


	World::World(int32_t w, int32_t h, Ball b, Paddle p, std::vector<Brick> bs):	WorldBall{b},WorldBricks{bs},w{w},h{h},WorldPadle{p}{};

	int32_t World::getWidth() const{
		return this->w;
	};
	int32_t World::getHeight() const{
		return this->h;
	};
	Ball World::getBall() const{
		return this->WorldBall;
	};
	Paddle World::getPaddle() const{
		return this ->WorldPadle;
	};
	std::vector<Brick> World::getBricks() const{
		return this-> WorldBricks;
	};
	bool World::isLegal() const{
		int velocities = abs(WorldBall.getVelocity().vx) + abs(WorldBall.getVelocity().vx);
			if(WorldBricks.size() < 1 || velocities == 0){
				std::cout<<"the velocities or number of bricks failed\n";
				return false;
			}
			// std::cout<<"velocities and bricks quantities passed\n";
			if(thingsCollide(this->WorldBricks,this->WorldPadle,this->WorldBall) ){ // check if any brick collide with each other or the paddle and ball
				return false;
			}
			else {
				// std::cout<<" bricks collision test passed\n";
			}


return true;
	};


std::ostream& operator<<(std::ostream& os, const std::vector<Brick>& bricks) {
	os << "[ ";
	for (auto const& b: bricks)
		os << b << "; ";
	os << "]";
	return os;
}

std::ostream& operator<<(std::ostream& os, const World& world) {
	os << "World {\n  width = " << world.getWidth() << "\n  height = " << world.getHeight() << "\n  " << world.getBall() << ",\n  " << world.getPaddle() << ",\n  " << world.getBricks() << "\n}";

	return os;
}
}
