#include "World.h"
#include <math.h>
#include <ostream>
#include <iostream>


using std::endl;
namespace arkanoid{
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
		int speed = abs(WorldBall.getVelocity().vx) + abs(WorldBall.getVelocity().vx);
			if(WorldBricks.size() < 1 || speed == 0){
				std::cout<<"the velocities or number of bricks failed\n";
				return false;
			}
			// std::cout<<"velocities and bricks quantities passed\n";
			if(BricksOrPaddleCollide(this->WorldBricks,this->WorldPadle,this->WorldBall) ){ // check if any brick collide with each other or the paddle and ball
				return false;
			}
			return true;
	};
	double distance(Point p1, Point p2){
		double  xsq = (p1.x - p2.x )* (p1.x - p2.x );
		double  ysq = (p1.y - p2.y )* (p1.y - p2.y );
		double result =  sqrt(xsq+ysq);
		return result;
	}


// bool circlecoll();
//squaredcoll detects a collision between any two squares.
bool squaredcoll(Point rec1, int32_t width1, int32_t height1, Point rec2, int32_t width2, int32_t height2){
		if (rec1.x <= rec2.x + width2 &&
				rec2.x <= rec1.x + width1  &&
				rec1.y <= rec2.y + height2 &&
				rec2.y <= rec1.y + height1){
					return true;
				};
		return false;
}
//general function that runs the tests between squares
bool World::BricksOrPaddleCollide(std::vector<Brick> bVect, Paddle pad, Ball ball) const{
		//check that no brick collides with another brick.
		for (unsigned j =0; j < bVect.size()-1; j++) {
			Point topleft = bVect[j].getUpperLeft();
			int32_t height = bVect[j].height;
			int32_t width = bVect[j].width;
			for (unsigned k =j+1; k < bVect.size(); k++) {
				Point topleft2 = bVect[k].getUpperLeft();
				int32_t height2 = bVect[k].height;
				int32_t width2 = bVect[k].width;
				if (squaredcoll(topleft,width,height,topleft2, width2,height2)){
					return true;
				}
			}
		}
		//check if any brick collides with the paddle.
		for (unsigned j =0; j < bVect.size(); j++) {
			Point topleft = bVect[j].getUpperLeft();
			int32_t height = bVect[j].height;
			int32_t width = bVect[j].width;
		 if(squaredcoll(topleft,width,height,pad.getUpperLeft(), pad.width, pad.height)){
			 return true;
	   }
		}

			//bricks don't collide means false
			return false;
};
bool World::BrickandBallCollide(std::vector<Brick> bVect, Ball ball) const{
	//this is the most process heavy function.
	// it checks every single edge of a brick, and sees if the distance of every
	// point to the center of the ball is less than the ball's radious
	//in that case the ball should bounce and the brick should disappear.

	//CODE:
	//the outer most loop iterates over every brick, the next loop iterates
	//for the height of the brick.
	//if the the current y component of the brick is at the beginning or at the end
	// iterate over the width of the block and test every single Point
	// otherwise test the two lateral points of the hollow brick.
	//this loop could assume the brick is full of points, but that is
	// a lot more inefficient. Here the number of comparisons is not a squared number
	//but width  + width + height + height. which is less than width X height

	int ballrad = ball.rad;
	for (size_t i = 0; i < bVect.size(); i++) {
		Point ballCenter = ball.getCenter();
		Point  brickTopLeft = bVect[i].getUpperLeft();

		for (size_t i = 0; i < bVect[i].height+1; i++) {
			// i+bVect[i].height  == brickTopLeft.y + bVect[i].height
			if (i == 0 ){
				for (size_t j = 0; j < bVect[i].width +1; j++ ) {
					Point p;
					p.x = brickTopLeft.x + j;
					p.y = brickTopLeft.y;
					if (ballrad <= distance(p,ball.getCenter()) ){
						bVect[i].life = 0;
						return true;
					}
				}
			}
			else if (i == bVect[i].height ){
				for (size_t j = 0; j < bVect[i].width +1; j++) {
					Point p;
					p.x = brickTopLeft.x + j;
					p.y = brickTopLeft.y + bVect[i].height;
					if (ballrad <= distance(p,ball.getCenter()) ){
						bVect[i].life = 0;
						return true;
					}
				}
			}
			else{
				Point p;
				p.x = brickTopLeft.x;
				p.y = brickTopLeft.y;
				Point p2;
				p2.x = brickTopLeft.x + brickTopLeft.x + bVect[i].width;
				p2.y = brickTopLeft.y;
				if(ballrad <= distance(p,ballCenter) || ballrad <= distance(p2,ballCenter)){
					bVect[i].life = 0;
					return true;
				}
			}
		}
	}
	return false;
}

bool World::BallPaddleCollide(Paddle paddle, Ball ball) const{
	return false;
}
void World::update(Input){

	for (size_t i = 0; i < abs((WorldBall.getVelocity()).vx); i++) {
		// update the position of the ball
		(WorldBall.center).x++;
		(WorldBall.center).y++;

		//Update paddle given input

		//if ball-brick collision
		BrickandBallCollide(WorldBricks,WorldBall);
		//if ball-paddle collision
		if(BallPaddleCollide(WorldBricks,WorldBall)){

		}
		//if ball edge collision


		}

}
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
