#include "LevelTrigger.h"
#include "Game.h"
#include "Camera.h"
#include "LevelManager.h"

LevelTrigger::LevelTrigger() {
}

//Load gameobject
void LevelTrigger::load(const LoadParameters parameters) {
	SDLGameObject::load(parameters);
	m_collider = { (int)m_position.getX(), (int)m_position.getY(), 16, 16 };
}

//Load the trigger's level if the player collides with it
void LevelTrigger::collision(std::string tag) {
	if (tag == "PLAYER") {
		LevelManager::instance()->changeLevel(levelID, m_newX, m_newY);
	}
}