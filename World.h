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
	int32_t w, h; // size of the board
	Paddle WorldPadle; // the player's paddle

	//constructor
	World(int32_t w, int32_t h, Ball b, Paddle p, std::vector<Brick> bs);

	//member functions
	int32_t getWorldWidth() const;
	int32_t getWorldHeight() const;
	Ball getBall() const;
	Paddle getPaddle() const;
	std::vector<Brick> getBricks() const;
	bool isLegal() const;
	void update(Input);
};

// The type of the exception that needs to be thrown when the game is over
class GameOverException: std::exception {};

}
