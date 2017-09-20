#include "DisplayGraphic.h"
#include "LevelManager.h"
#include "Game.h"

//Load gameobject
void DisplayGraphic::load(LoadParameters parameters) {
	SDLGameObject::load(parameters);
	m_heartObject = new SDLGameObject();
	m_heartObject->load(LoadParameters(0, 128, 16, 16, "heart"));
	m_playerRef = LevelManager::instance()->getCurrentLevel()->getPlayer();
	m_heartAmount = m_playerRef->getHealth();
	m_hitTimer = m_maxTimer = 2;
	m_hit = false;
}

//Keep the heart GUI updated to match the player's health
void DisplayGraphic::update() {
	m_playerRef = LevelManager::instance()->getCurrentLevel()->getPlayer();
	if (m_playerRef != NULL) {
		if (m_playerRef->getHealth() < m_heartAmount) {
			m_heartAmount = m_playerRef->getHealth();
			m_hit = true;
		}
	}
	else {
		m_playerRef = LevelManager::instance()->getCurrentLevel()->getPlayer();
		m_heartAmount = m_playerRef->getHealth();
	}

	if (m_hit) {
		m_hitTimer--;
		if (m_hitTimer < 0) {
			m_hit = false;
			m_hitTimer = m_maxTimer;
		}
	}
}

//If the player is hit, draw a blank color to the screen
//Also draw the correct amount of hearts the player has
void DisplayGraphic::draw() {
	if (m_hit) {
		SDL_SetRenderDrawColor(Game::instance()->getRenderer(), 0xF3, 0xD2, 0x6D, 0xFF);
		SDL_RenderClear(Game::instance()->getRenderer());
	}
	SDLGameObject::draw();

	for (int i = 0; i < m_heartAmount; i++) {
		m_heartObject->getPosition().setX((i * 16));
		m_heartObject->draw();
	}
}

void DisplayGraphic::clean() {
	delete m_heartObject;
}