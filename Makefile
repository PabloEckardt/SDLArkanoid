CC = g++ -std=c++14

OBJS = Paddle.cpp Brick.cpp Point.cpp Ball.cpp World.cpp main.cpp Ball.cpp

OBJ_NAME = main

LINKER_FLAGS = -lSDL2

COMPILER_FLAGS = 

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) $ -o $(OBJ_NAME)
