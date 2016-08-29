#pragma once

#include "Ball.h"
#include "Brick.h"
#include "Input.h"
#include "Paddle.h"

#include <iosfwd>
#include <vector>

namespace arkanoid
{

class World
{
public:
	// members
	Ball WorldBall; // the game's ball
	std::vector<Brick> WorldBricks; //all bricks will be contained and deleted from this vector.
	int32_t w = 720;
	int32_t h = 480; // size of the board
	Paddle WorldPadle; // the player's paddle
	short gameLive = 1;// 1 while the game is running, 0 when its over.
	//constructor
	World( Ball b, Paddle p);

	//member functions
	//getters
	int32_t getWorldWidth() const;
	int32_t getWorldHeight() const;
	Ball getBall() const;
	Paddle getPaddle() const;
	std::vector<Brick> getBricks() const;

	//detect collisions between bricks and bricks or bricks and paddles.
	bool twoRectCollision(Point p1, int w1, int h1, Point p2, int w2, int h2)const;
	//collisions between the ball and any rectangle.
	bool circleRectCollision(Point rect, int widthRect, int heightRect, Ball ball)const;
	// checks that nothing is overlapping, and everything is placed properly.
	bool isValid() const;
	// updates once per tick of the game.
	void update();
};

// The type of the exception that needs to be thrown when the game is over
class GameOverException: std::exception {};

}
