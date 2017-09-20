#include "Relic.h"
#include "Game.h"
#include "Camera.h"
#include "LevelManager.h"

Relic::Relic() {
}


//Load gameobject
void Relic::load(const LoadParameters parameters) {
	SDLGameObject::load(parameters);
	m_collider = { (int)m_position.getX(), (int)m_position.getY(), 16, 16 };
	m_taken = false;
}

//Offset drawing from camera position
void Relic::draw() {
	m_position.modX(-Camera::instance()->getPosition().getX());
	m_position.modY(-Camera::instance()->getPosition().getY());
	SDLGameObject::draw();
	m_position.modX(Camera::instance()->getPosition().getX());
	m_position.modY(Camera::instance()->getPosition().getY());
}

//Animate every frame
void Relic::update() {
	m_collider.x = m_position.getX();
	m_collider.y = m_position.getY();

	m_currentFrame = int((SDL_GetTicks() / 175) % 9);
}

void Relic::clean() {
}

//Set the victory condition to true if player collision
void Relic::collision(std::string tag) {
	if (tag == "PLAYER") {
		LevelManager::instance()->getCurrentLevel()->getPlayer()->setVictory(true);
	}
}