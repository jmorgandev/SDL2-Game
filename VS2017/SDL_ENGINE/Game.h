#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <vector>
#include "EventHandler.h"

enum class WindowMode { Windowed, Fullscreen, BorderlessFullscreen};

//Main game class
class Game {
public:
	static Game* instance();
	~Game(){}

	bool init(const char* title, int scale, WindowMode mode = WindowMode::Windowed);
	void render();
	void update();
	void handleEvents();
	void quit();
	void clean();

	void changeWindowMode(WindowMode newMode);

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
	int m_ScreenScale;

	WindowMode m_windowMode;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;
};

#endif