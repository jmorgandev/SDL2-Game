#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <vector>
#include "EventHandler.h"

//Main game class
class Game {
public:
	static Game* instance();
	~Game(){}

	bool init(const char* title, int xpos, int ypos, int width, int height, int scale, bool fullscreen);
	void render();
	void update();
	void handleEvents();
	void quit();
	void clean();

	void addEventHandler(EventHandler* pHandler);
	void removeEventHandler(EventHandler* pHandler);

	bool running() { return m_bRunning; }
	SDL_Renderer* getRenderer() { return m_pRenderer; }

	int getScreenWidth();
	int getScreenHeight();

private:
	Game() {}

	int m_ScreenWidth;
	int m_ScreenHeight;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;
};

#endif