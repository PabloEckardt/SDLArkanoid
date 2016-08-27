#include "World.h"
#include <math.h>
#include <ostream>
#include <iostream>


using std::endl;
namespace arkanoid{
	World::World(int32_t w, int32_t h, Ball b, Paddle p, std::vector<Brick> bs):	WorldBall{b},WorldBricks{bs},w{w},h{h},WorldPadle{p}{};

	int32_t World::getWorldWidth() const{
		return this->w;
	};
	int32_t World::getWorldHeight() const{
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
	// 	int speed = abs(WorldBall.getVelocity().vx) + abs(WorldBall.getVelocity().vx);
	// 		if(WorldBricks.size() < 1 || speed == 0){
	// 			std::cout<<"the velocities or number of bricks failed\n";
	// 			return false;
	// 		}
	// 		// std::cout<<"velocities and bricks quantities passed\n";
	// 		if(BricksOrPaddleCollide(this->WorldBricks,this->WorldPadle,this->WorldBall) ){ // check if any brick collide with each other or the paddle and ball
	// 			return false;
	// 		}
			return true;
	};
	double distance(Point p1, Point p2){
		double  xsq = (p1.x - p2.x )* (p1.x - p2.x );
		double  ysq = (p1.y - p2.y )* (p1.y - p2.y );
		double result =  sqrt(xsq+ysq);
		return result;
	}

	void World::update(Input){

	}
}
