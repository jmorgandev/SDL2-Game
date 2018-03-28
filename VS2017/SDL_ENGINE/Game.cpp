#include "Game.h"
#include "GameStateMachine.h"
#include "EventPoller.h"
#include "MainMenuState.h"
#include "TextureManager.h"
#include "GameObjectFactory.h"
#include <stdio.h>

#include "Button.h"
#include "StaticImage.h"
#include "ScrollingImage.h"
#include "Player.h"
#include "Enemy.h"
#include "DisplayGraphic.h"
#include "Relic.h"
#include "LevelTrigger.h"

const int VID_WIDTH = 160;
const int VID_HEIGHT = 144;
const int VID_SCALE = 4;
const double VID_ASPECT = (double)VID_WIDTH / (double)VID_HEIGHT;

Game* Game::instance() {
	static Game game_instance;
	return &game_instance;
}

int Game::getScreenWidth(){
	return m_ScreenWidth;
}
int Game::getScreenHeight() {
	return m_ScreenHeight;
}

void Game::changeWindowMode(WindowMode newMode) {
	switch (newMode) {
	case WindowMode::Windowed:
		m_ScreenWidth = VID_WIDTH;
		m_ScreenHeight = VID_HEIGHT;
		SDL_SetWindowFullscreen(m_pWindow, SDL_FALSE);
		SDL_SetWindowBordered(m_pWindow, SDL_TRUE);
		SDL_SetWindowSize(m_pWindow, m_ScreenWidth*m_ScreenScale, m_ScreenHeight*m_ScreenScale);
		SDL_SetWindowPosition(m_pWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		m_windowMode = newMode;
		break;
	case WindowMode::Fullscreen:
		m_ScreenWidth = VID_WIDTH;
		m_ScreenHeight = VID_HEIGHT;
		SDL_SetWindowSize(m_pWindow, m_ScreenWidth*m_ScreenScale, m_ScreenHeight*m_ScreenScale);
		SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN);
		m_windowMode = newMode;
		break;
	case WindowMode::BorderlessFullscreen: {
			changeWindowMode(WindowMode::Windowed);
			SDL_DisplayMode dm;
			if (SDL_GetDesktopDisplayMode(0, &dm) == 0) {
				m_ScreenHeight = dm.h;
				m_ScreenWidth = dm.h * VID_ASPECT;
				SDL_SetWindowSize(m_pWindow, m_ScreenWidth, m_ScreenHeight);
				SDL_SetWindowBordered(m_pWindow, SDL_FALSE);
				SDL_SetWindowPosition(m_pWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
				m_windowMode = newMode;
			}
			else {
				printf("Can't detect native resolution, switching to windowed mode...");
			}
		} break;
	}
}

//Initialise the SDL window to the scaled resolution
//and then set the internal resolution to the passed width and height arguments
bool Game::init(const char* title, int scale, WindowMode mode) {
	m_ScreenWidth = VID_WIDTH;
	m_ScreenHeight = VID_HEIGHT;
	m_ScreenScale = scale;
	int flags = SDL_WINDOW_SHOWN;
		
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Failed to initialise SDL. Error: %s", SDL_GetError());
		return false;
	}
	int p = SDL_WINDOWPOS_CENTERED;
	m_pWindow = SDL_CreateWindow(title, p, p, m_ScreenWidth*m_ScreenScale, m_ScreenHeight*m_ScreenScale, flags);
	if (m_pWindow == nullptr) {
		printf("Failed to create SDL Window. Error: %s", SDL_GetError());
		return false;
	}
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
	if (m_pRenderer == nullptr) {
		printf("Failed to create SDL Renderer. Error: %s", SDL_GetError());
		return false;
	}
	SDL_RenderSetLogicalSize(m_pRenderer, m_ScreenWidth, m_ScreenHeight);
	SDL_SetRenderDrawColor(m_pRenderer, 0xFB, 0xD8, 0xB8, 0xFF);
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 0xFF);

	changeWindowMode(WindowMode::Windowed);

	//Add every gameobject type to the GameObjectFactory
	GameObjectFactory::instance()->registerType("Image", new StaticImageCreator());
	GameObjectFactory::instance()->registerType("Button", new ButtonCreator());
	GameObjectFactory::instance()->registerType("Player", new PlayerCreator());
	GameObjectFactory::instance()->registerType("Enemy", new EnemyCreator());
	GameObjectFactory::instance()->registerType("ScrollingImage", new ScrollingImageCreator());
	GameObjectFactory::instance()->registerType("DisplayGraphic", new DisplayGraphicCreator());
	GameObjectFactory::instance()->registerType("LevelTrigger", new LevelTriggerCreator());
	GameObjectFactory::instance()->registerType("Relic", new RelicCreator());

	GameStateMachine::instance()->changeState(new MainMenuState);

	m_bRunning = true;

	return true;
}

//Render the current gamestate
void Game::render() {
	SDL_RenderClear(m_pRenderer);

	GameStateMachine::instance()->render();

	SDL_RenderPresent(m_pRenderer);
}

//Add an event handler to the Event Poller
void Game::addEventHandler(EventHandler* pHandler) {
	EventPoller::instance()->addHandler(pHandler);
}

//Remove an event handler from the Event Poller
void Game::removeEventHandler(EventHandler* pHandler) {
	EventPoller::instance()->removeHandler(pHandler);
}

//Poll SDL Events using Event Poller
void Game::handleEvents() {
	EventPoller::instance()->update();
}

//Update the current GameState
void Game::update() {
	GameStateMachine::instance()->update();
}

//Quit the program
void Game::quit() {
	m_bRunning = false;
}


//Clean up everything
void Game::clean() {
	GameStateMachine::instance()->clean();
	EventPoller::instance()->clean();
	TextureManager::instance()->clean();
	GameObjectFactory::instance()->clean();

	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}