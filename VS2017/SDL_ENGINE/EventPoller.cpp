#include "EventPoller.h"
#include "Game.h"
#include <algorithm>

EventPoller* EventPoller::instance() {
	static EventPoller eventPoller_instance;
	return &eventPoller_instance;
}

//Add an EventHandler interface to the subscriber list
void EventPoller::addHandler(EventHandler* pHandler) {
	m_handlers.push_back(pHandler);
}

//Remove an EventHandler interface from the subscriber list
void EventPoller::removeHandler(EventHandler* pHandler) {
	m_handlers.erase(std::remove(m_handlers.begin(), m_handlers.end(), pHandler), m_handlers.end());
}

//Poll SDL for events, and send the events to every Event Handler in the subscriber list
void EventPoller::update() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			Game::instance()->quit();
		}
		else {
			//Extra window size controls for showcasing
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_F4:
					Game::instance()->changeWindowMode(WindowMode::Windowed);
					break;
				case SDLK_F5:
					Game::instance()->changeWindowMode(WindowMode::Fullscreen);
					break;
				}
			}
			for (int i = 0; i < m_handlers.size(); i++) {
				m_handlers[i]->handleEvent(e);
			}
		}
	}
}

void EventPoller::clean() {
	m_handlers.clear();
}