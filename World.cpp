#include "World.h"
#include <math.h>
#include <ostream>
#include <iostream>

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gOpening = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

using std::endl;

	World::World( Ball b, Paddle p):	WorldBall{b},WorldPadle{p}{
		gameLive = 1;
		w = 720;
		h = 480;
		WorldBricks = { }; // make sure the vector of bricks is empty

		for (size_t i = 1; i < 7; i++) // 6 rows of bricks.
			for (size_t j = 20; j < 460; j+=40) { // 23 columns
				// The brick constructor has a point, width, and a height.
				//this loop places them in  a way they are in valid positions.
				Brick tempBrick( {j-1,(i*20) + 1}, 40, 20);
				WorldBricks.push_back(tempBrick);
			}
		// this will display all the bricks that are going to be generated
		// for (size_t i = 0; i < WorldBricks.size(); i++) {
		// 	WorldBricks.at(i).displayPoint();
		// }
	};


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

	//twoRectCollision
	bool World::twoRectCollision(Point p1, int w1, int h1, Point p2, int w2, int h2)const{
	 if (p1.x < p2.x + w2 &&
   		p1.x + w1 > p2.x &&
   		p1.y < p2.y + h2 &&
   		h1 + p1.y > p2.y   )
				return true;
		else
			return false;
	}
	//circleRectCollision
	bool World::circleRectCollision(Point rect, int widthRect, int heightRect, Ball ball)const{
	// return true if the rectangle and circle are colliding
	// function RectCircleColliding(circle,rect){
	//     var distX = Math.abs(circle.x - rect.x-rect.w/2);
	//     var distY = Math.abs(circle.y - rect.y-rect.h/2);
	//
	//     if (distX > (rect.w/2 + circle.r)) { return false; }
	//     if (distY > (rect.h/2 + circle.r)) { return false; }
	//
	//     if (distX <= (rect.w/2)) { return true; }
	//     if (distY <= (rect.h/2)) { return true; }
	//
	//     var dx=distX-rect.w/2;
	//     var dy=distY-rect.h/2;
	//     return (dx*dx+dy*dy<=(circle.r*circle.r));
	// }
	int xDist  = abs(rect.x + widthRect/2 - ball.pt.x);
	int yDist = abs(rect.x + heightRect/2 - ball.pt.y);

	if (xDist > (ball.rad + widthRect/2)) { return false;}
	if (yDist > (ball.rad + heightRect/2)) { return false;}

	if(xDist <= (widthRect/2)) {return true;}
	if(yDist <= (heightRect/2)) {return true;}

	float dx = xDist - widthRect/2;
	float dy = yDist - heightRect/2;
	return ((dx*dx + dy*dy) <= (ball.rad * ball.rad));

	}


	bool World::isValid() const{
		// this checks all bricks against each others.
		for (size_t i = 0; i < WorldBricks.size(); i++) {
			for (size_t j = i; j < WorldBricks.size(); j++){
				if ( i != j ){
					Point p1 = (WorldBricks.at(i).leftup);
					int w1 = (WorldBricks.at(i).width);
					int h1 = (WorldBricks.at(i).height);

					Point p2 = (WorldBricks.at(j).leftup);
					int w2 = (WorldBricks.at(j).width);
					int h2 = (WorldBricks.at(j).height);

					if (twoRectCollision(p1,w1,h1,p2,w2,h2 )){
						//debugging print statements in case it fails.
						// std::cout << "returning false " << i << "  " << j << std::endl;
						// std::cout << "p1.x " << p1.x << " p2.x " << p2.x  << std::endl;
						return false;
					}
				}
			}
		}
		// check all bricks against the ball.
		for (size_t i = 0; i < WorldBricks.size(); i++) {
			if (circleRectCollision(WorldBricks.at(i).leftup,WorldBricks.at(i).width,WorldBricks.at(i).height,WorldBall  )){
				return false;
			}
		}

		return true;
	};



	double distance(Point p1, Point p2){
		double  xsq = (p1.x - p2.x )* (p1.x - p2.x );
		double  ysq = (p1.y - p2.y )* (p1.y - p2.y );
		double result =  sqrt(xsq+ysq);
		return result;
	}

	void World::update(){
		int liveBricks = WorldBricks.size();
		for (size_t i = 0; i < WorldBricks.size(); i++) {
			if (circleRectCollision(WorldBricks.at(i).leftup,WorldBricks.at(i).width,WorldBricks.at(i).height,WorldBall) && WorldBricks.at(i).live){
				liveBricks --;
				WorldBricks.at(i).live = 0;
				WorldBall.vel.vy *= -1;
				break;
			}
		}

		// If the ball hits lower bound, end the game and freeze the program.
		if(WorldBall.pt.y + WorldBall.rad >= 480 ){
			gameLive = 0;
		}
		// if all bricks are dead, end the game and freeze the program.
		if (liveBricks == 0){
			gameLive = 0;
		}
		// check that the ball hasn't gone out of bounds.
		if (WorldBall.pt.x - WorldBall.rad <= 0 || WorldBall.pt.x + WorldBall.rad >= 720 ){
			WorldBall.vel.vx *=-1;
		}
		if(WorldBall.pt.y  - WorldBall.rad <= 0){
			WorldBall.vel.vy *=-1;
		}
		// check that the paddle hasn't gone out of bounds
		int padLeftFlag = 1;
		int padRightFlag = 1;
		if(WorldPadle.pt.x <= 0 ){
			padLeftFlag = 0;
		}
		if(WorldPadle.pt.x + WorldPadle.width >= 720 ){
			padRightFlag = 0;
		}
		// Check if the ball has hit the paddle;
		//we can do this later.
		// take input
		//wait until we can do it in SDL
		// make everything move.
		WorldBall.pt.x += WorldBall.vel.vx;
		WorldBall.pt.y += WorldBall.vel.vy;

		int inputVar = 0; //0 left 1 right 2 none
		if(inputVar == 0 && padLeftFlag){
			WorldPadle.pt.x -= WorldPadle.DefaultVelocity;
		}
		if(inputVar == 1 && padRightFlag){
			WorldPadle.pt.x += WorldPadle.DefaultVelocity;
		}

	}
	void World::drawWorld(){
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
    
    for (size_t i = 0; i < WorldBricks.size(); i++) {
            if ( WorldBricks.at(i).live ){
				// make filled rect object
			    SDL_Rect filledRect = {WorldBricks.at(i).leftup.x, WorldBricks.at(i).leftup.y, WorldBricks.at(i).width,WorldBricks.at(i).height};// make rectangle structure
				SDL_SetRenderDrawColor(gRenderer,0x00,0x00,0x00,0xFF);
	            SDL_RenderFillRect(gRenderer,&filledRect);
				SDL_RenderPresent( gRenderer );
              }
      }
	}
