#include "World.h"
#include <iostream>
#include <cstdlib>

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 480;

int main() {
	// SDL Rendering window.
	SDL_Window * window = NULL;
	SDL_Surface * screenSurface = NULL;
	//init SDL2
	 if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		 printf( "SDL could not initialize SDL_Error: %s\n", SDL_GetError() );
	 }
	 else {
		 //creating the window with the constant target values
		 window = SDL_CreateWindow( "Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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
	//
	Ball ball = {{360, 240}, 5, {-1, 1}};
	Paddle paddle = {{360, 459}, 20, 10, 1};
	World world = { ball, paddle};

	std::cout << "is valid = " << world.isValid() << std::endl;
	SDL_Event e;
	while (world.gameLive){
			// world.update();
			SDL_PollEvent( &e );
		if (e.type == SDL_QUIT){
			world.gameLive = 0;
		}
		if (e.type == SDL_KEYDOWN){
			printf("pressed value %d", e.key.keysym.sym);
		}
		world.drawWorld();
	}
	//Destroy window
	SDL_DestroyWindow(window);
	//qui SDL
	SDL_Quit();
	return 0;
}
