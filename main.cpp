#include "World.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <cstdlib>

using namespace arkanoid;

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 480;

int main() {

	/*
	0,0--------------------
	|	   	b r i c k s			|
	|											|
	|				ball				  |
	|											|
	---------paddle------720,480
	*/

	// SDL Rendering window.
	SDL_Window * window = NULL;
	SDL_Surface * screenSurface = NULL;
	//init SDL2
	 if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		 printf( "SDL could not initialize SDL_Error: %s\n", SDL_GetError() );
	 }
	 else {
		 //creating the window with the constant target values
		 window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		 if( window == NULL ) {
			  printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			}
			else {
				//get window surface
				screenSurface = SDL_GetWindowSurface(window);
				//fill surface with white
				SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format,255,255,255));
				//update it
				SDL_UpdateWindowSurface(window);
				//wait in ms
				SDL_Delay(2000);
			}
	}
	Ball ball = {{360, 240}, 5, {-1, 1}};
	Paddle paddle = {{360, 459}, 20, 10, 1};
	World world = { ball, paddle};

	std::cout << "is valid = " << world.isValid() << std::endl;
	while (world.gameLive){
		// world.update();
	}
	// Uncomment the following lines after you finish World::update()
	//world.update(Input::Left);
	//std::cout << world << std::endl;
}
