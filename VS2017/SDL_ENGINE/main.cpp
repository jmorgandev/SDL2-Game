#include "Game.h"


const int FPS = 60;		//FPS Limit
const int DELAY_TIME = 1000.0f / FPS;	//How many ticks must elapse before next frame

int main(int argc, char* args[]) {

	Uint32 frameStart, frameTime;	//Variables for framerate limit

	Game::instance()->init("Into the Fold", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 160, 144, 4, false);


	//If init was successful then begin running game until the game quits
	while (Game::instance()->running()) {
		frameStart = SDL_GetTicks();

		Game::instance()->handleEvents();	//Handle all game events
		Game::instance()->update();			//Update gameobjects
		Game::instance()->render();			//Render gameobjects

		frameTime = SDL_GetTicks() - frameStart;	//Assign elapsed ticks minus framestart to frameTime,
		//This gives how many ticks the previous frame took to run

		//If the frameTime in ticks took less than the desired amount of ticks
		if (frameTime < DELAY_TIME) {
			SDL_Delay((int)(DELAY_TIME - frameTime));	//Delay SDL by the amount of ticks needed to reach the desired amount
		}
	}
	Game::instance()->clean();	//If the game is quit, clean all memory to prevent leaks

	return 0;
}