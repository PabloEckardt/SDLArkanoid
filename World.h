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
	// Implement the member functions listed below
		Ball WorldBall;
		std::vector<Brick> WorldBricks;
		int32_t w, h;
		Paddle WorldPadle;
	World(int32_t w, int32_t h, Ball b, Paddle p, std::vector<Brick> bs);


	bool BricksOrPaddleCollide(std::vector<Brick> bricks,Paddle pad, Ball ball) const;
	bool BrickandBallCollide(std::vector<Brick> bVect, Ball ball) const;
	bool BallPaddleCollide(Paddle paddle, Ball ball) const;

	int32_t getWidth() const;
	int32_t getHeight() const;
	Ball getBall() const;
	Paddle getPaddle() const;
	std::vector<Brick> getBricks() const;

	bool isLegal() const;
	void update(Input);
};

// The type of the exception that needs to be thrown when the game is over
class GameOverException: std::exception {};

// Additional logic to let std::cout work with World objects
std::ostream& operator<<(std::ostream&, const std::vector<Brick>&);
std::ostream& operator<<(std::ostream&, const World&);

}
