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

//Initialise the SDL window to the scaled resolution
//and then set the internal resolution to the passed width and height arguments
bool Game::init(const char* title, int xpos, int ypos, int width, int height, int scale, bool fullscreen) {
	m_ScreenWidth = width;
	m_ScreenHeight = height;
	int flags = 0;
	flags = (fullscreen) ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN;
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Failed to initialise SDL. Error: %s", SDL_GetError());
		return false;
	}
	m_pWindow = SDL_CreateWindow(title, xpos, ypos, width*scale, height*scale, flags);
	if (m_pWindow == nullptr) {
		printf("Failed to create SDL Window. Error: %s", SDL_GetError());
		return false;
	}
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
	if (m_pRenderer == nullptr) {
		printf("Failed to create SDL Renderer. Error: %s", SDL_GetError());
		return false;
	}
	SDL_RenderSetLogicalSize(m_pRenderer, width, height);
	SDL_SetRenderDrawColor(m_pRenderer, 0xFB, 0xD8, 0xB8, 0xFF);
	
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